// TO DO:
// prevent I2C bus lock-up
// website alarm

#include <Arduino.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <RTClib.h>
#include <NTPClient.h>
#include <Wire.h>
#include <FS.h>
#include <SPIFFS.h>

#include "config.h"
#include "globals.h"

#include "modules/commands.h"
#include "modules/states.h"
#include "modules/sending.h"
#include "modules/measurements.h"
#include "modules/sockets.h"
#include "modules/time.h"

#include "myEventLister.h"
#include "myWiFi.h"
#include "myJsonStorage.h"

// new event lister
static myEventLister eventLister;

void setup() {
  bool success;

  pinMode(pin_IN_1, INPUT);
  pinMode(pin_IN_2, INPUT);
  pinMode(pin_IN_3, INPUT);
  pinMode(pin_IN_4, INPUT);
  pinMode(pin_IN_5, INPUT);
  pinMode(pin_IN_6, INPUT);
  pinMode(pin_OUT_1, OUTPUT);
  pinMode(pin_OUT_2, OUTPUT);
  pinMode(pin_OUT_3, OUTPUT);
  pinMode(pin_OUT_4, OUTPUT);

  states.IN_1 = digitalRead(pin_IN_1);
  states.IN_2 = digitalRead(pin_IN_2);
  states.IN_3 = digitalRead(pin_IN_3);
  states.IN_4 = digitalRead(pin_IN_4);
  states.IN_5 = digitalRead(pin_IN_5);
  states.IN_6 = digitalRead(pin_IN_6);
  states.OUT_1 = digitalRead(pin_OUT_1);
  states.OUT_2 = digitalRead(pin_OUT_2);
  states.OUT_3 = digitalRead(pin_OUT_3);
  states.OUT_4 = digitalRead(pin_OUT_4);

  sensors.setResolution(9); // set resolution of DS18B20 sensors to 9 bit

  Serial.begin(115200);
  Serial.setDebugOutput(false);

  // inicialize Wire and join I2C bus as controller
  Serial.print("Initializing I2C bus... ");
  Wire.begin(pin_SDA, pin_SCL);
  Serial.println("Done.");

  // inicialiaze sensors
  Serial.print("Initializing Sensors... ");
  sensors.begin();
  Serial.println("Done.");

  // start RTC
  Serial.print("Starting RTC... ");
  success = rtc.begin();
  if(success){
    Serial.print("RTC started. Actual RTC datetime: ");
    DateTime now = rtc.now();
    char buffer[22] = "DD. MM. YYYY hh:mm:ss";
    Serial.println(now.toString(buffer));
  } else {
    Serial.println("Failed to start RTC.");
  }
  // assign value to lastPumpOn
  lastPumpOn = DateTime(rtc.now().unixtime());
  
  // try to connect to the WiFi network
  Serial.print("Connecting to WiFi network... ");
  success = wifi.connect(WIFI_SSID, WIFI_PASSWORD, WIFI_TIMEOUT);
  if(success){
    Serial.println("WiFi connected.");
  } else {
    Serial.println("Connection failed.");
  }

  // start Wifi UDP socket
  Serial.print("Starting WiFi UDP socket... ");
  success = udp.begin(UDP_PORT);
  if(success){
    Serial.println("WiFi UDP socket started.");
  } else {
    Serial.println("Failed to start WiFi UDP socket.");
  }

  // initialize WebSocket client
  Serial.print("Initializing WebSocket client... ");
  socket.beginSSL(WS_HOST, WS_PORT, WS_PATH);
  socket.onEvent(webSocketEvent);
  socket.setReconnectInterval(100);
  Serial.println("Done.");

  // initialize NTP client
  Serial.print("Initializing NTP client... ");
  timeClient.begin();
  Serial.println("Done.");

  // format SPIFFS (only for debuging)
  // SPIFFS.format();

  // initialize json storages
  Serial.print("Initializing json storage for unsent data on SPIFFS... ");
  success = unsentMeasurements.begin();
  if(success){
    Serial.println("Done.");
  } else {
    Serial.println("Failed to initialize storage.");
  }
  Serial.print("Initializing json storage for unsent states on SPIFFS... ");
  success = unsentStates.begin();
  if(success){
    Serial.println("Done.");
  } else {
    Serial.println("Failed to initialize storage.");
  }

  // print actual SPIFFS usage
  Serial.print("SPIFFS usage: ");
  Serial.print(SPIFFS.usedBytes());
  Serial.print("/");
  Serial.print(SPIFFS.totalBytes());
  Serial.println(" bytes");

  // add events to event list
  Serial.print("Adding events... ");
  eventLister.addRepeatedEvent(syncTime, 12*3600*1000); // add event: syncTime every 12 hours
  eventLister.addRepeatedEvent(handleMeasuring, 20000); // add event: sendMeasurements every 20 seconds
  eventLister.addRepeatedEvent(checkWebSocket, 500); // add event: chekWebSocket every 500 miliseconds
  eventLister.addRepeatedEvent(checkStatesForChanges, 100); // add event: checkStatesForChanges every 100 miliseconds
  Serial.println("Done.");

  // take three measurements to fill the lastSensorsData arrays
  takeMeasurement();
  takeMeasurement();
  takeMeasurement();

  // send states to the server
  sendStates();
}

void loop() {
  eventLister.loop();
  // check serial for icoming command
  if(Serial.available()>0){
    String command = Serial.readStringUntil('\n'); // get incoming command
    while(Serial.available()>0){
      Serial.read();
    }
    executeSerialCommand(command); // execute incoming command
  }
  // check wifi connection
  if(!wifi.connected()){
    // try to connect to the WiFi network
    Serial.print("Wifi is disconnected. Connecting to WiFi network... ");
    bool success = wifi.connect(WIFI_SSID, WIFI_PASSWORD, WIFI_TIMEOUT);
    if(success){
      Serial.println("WiFi connected.");
    } else {
      Serial.println("Connection failed.");
    }
  }
  // turn off pump after PUMP_ON_DURATION
  if(digitalRead(pin_OUT_1) == HIGH){
    if((rtc.now().unixtime()-lastPumpOn.unixtime()) >= PUMP_ON_DURATION){
      Serial.println("[CONTROL] Pump off.");
      digitalWrite(pin_OUT_1, LOW);
      checkStatesForChanges();
    }
  }
}