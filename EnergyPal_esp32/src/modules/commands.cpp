#include "modules/commands.h"
#include "config.h"
#include "globals.h"
#include "modules/states.h"
#include "myWiFi.h"
#include "myJsonStorage.h"
#include <WebSocketsClient.h>
#include <Arduino.h>
#include <ArduinoJson.h>

// execute command from serial
void executeSerialCommand(String command){
    Serial.print("Executing command: ");
    Serial.println(command);
    // get command content
    String operation = "";
    String identifier = "";
    String value = "";
    int i = 0;
    for(; command[i] != ' '; i++){
      operation += command[i];
    }
    i++;
    for(; (command[i] != '\0') and (command[i] != ' '); i++){
      identifier += command[i];
    }
    if(command[i] == ' '){
      i++;
      for(; command[i] != '\0'; i++){
        value += command[i];
      }
    }
    // execute serial command
    // WIFI
    if(operation == "wifi"){
      if(identifier == "connect"){
        Serial.print("Connecting to WiFi network... ");
        bool success = wifi.connect(WIFI_SSID, WIFI_PASSWORD, 5000);
        if(success){
        Serial.println("WiFi connected.");
        } else {
          Serial.println("Connection failed.");
        }
      } else if(identifier == "disconnect"){
        wifi.disconnect();
        Serial.println("Wifi disconnected.");
      } else{
        Serial.println("Command does not exist.");
      }
    } 
    // PRINTING DATA
    else if(operation == "print"){
      if(identifier == "unsent"){
        if(value == "measurements"){
          unsentMeasurements.printAll();
        } else if(value == "states"){
          unsentStates.printAll();
        } else{
          Serial.println("Command does not exist.");  
        }
      } else{
        Serial.println("Command does not exist.");
      }
    }
    // SETTING OUTPUTS
     else if(operation == "setout"){
      int pin;
      bool identifierCorrect = true;
      if(identifier == "1"){
        pin = pin_OUT_1;
      } else if(identifier == "2"){
        pin = pin_OUT_2;
      } else if(identifier == "3"){
        pin = pin_OUT_3;
      } else if(identifier == "4"){
        pin = pin_OUT_4;
      } else{
        identifierCorrect = false;
        Serial.println("Command does not exist.");
      }
      if(identifierCorrect){
        if(value == "high"){
          digitalWrite(pin, HIGH);
          Serial.println("OUT_" + identifier + " set to HIGH");
        } else if(value == "low"){
          digitalWrite(pin, LOW);
          Serial.println("OUT_" + identifier + " set to LOW");
        } else {
          Serial.println("Command does not exist.");
        }
      }
    } else {
      Serial.println("Command does not exist.");
    }
  }

  // execute server command
void executeServerCommand(String operation, int value){
  if(operation == "outon"){
    switch(value){
      case 1:
      lastPumpOn = rtc.now();
      digitalWrite(pin_OUT_1, HIGH);
      break;
      case 2:
      digitalWrite(pin_OUT_2, HIGH);
      break;
      case 3:
      digitalWrite(pin_OUT_3, HIGH);
      break;
      case 4:
      digitalWrite(pin_OUT_4, HIGH);
      break;
    }
  }
  else if(operation == "outoff"){
    switch(value){
      case 1:
      digitalWrite(pin_OUT_1, LOW);
      break;
      case 2:
      digitalWrite(pin_OUT_2, LOW);
      break;
      case 3:
      digitalWrite(pin_OUT_3, LOW);
      break;
      case 4:
      digitalWrite(pin_OUT_4, LOW);
      break;
    }
  } 
  else if(operation == "ping"){
    JsonDocument pongDoc;
    JsonObject pongObject = pongDoc.to<JsonObject>();
    pongObject["action"] = "sendmessage";
    pongObject["deviceID"] = ENERGYPAL_ID;
    pongObject["operation"] = "pong";
    pongObject["value"] = value;
    String payload;
    serializeJson(pongDoc, payload);
    socket.sendTXT(payload);
  }
  checkStatesForChanges();
}
