#include "config.h"
#include "globals.h"
#include "modules/states.h"
#include "modules/sending.h"
#include "modules/math.h"
#include <ArduinoJson.h>
#include <DallasTemperature.h>
#include <RTClib.h>

// shift arrays of last measurements and take new measurement
void takeMeasurement(){
  sensors.requestTemperatures(); // request temps from sensors

  // shift arrays
  lastSensorsData.timestamp[2] = lastSensorsData.timestamp[1];
  lastSensorsData.temp1[2] = lastSensorsData.temp1[1];
  lastSensorsData.temp2[2] = lastSensorsData.temp2[1];
  lastSensorsData.temp3[2] = lastSensorsData.temp3[1];
  lastSensorsData.temp4[2] = lastSensorsData.temp4[1];
  lastSensorsData.temp5[2] = lastSensorsData.temp5[1];
  lastSensorsData.temp6[2] = lastSensorsData.temp6[1];
  
  lastSensorsData.timestamp[1] = lastSensorsData.timestamp[0];
  lastSensorsData.temp1[1] = lastSensorsData.temp1[0];
  lastSensorsData.temp2[1] = lastSensorsData.temp2[0];
  lastSensorsData.temp3[1] = lastSensorsData.temp3[0];
  lastSensorsData.temp4[1] = lastSensorsData.temp4[0];
  lastSensorsData.temp5[1] = lastSensorsData.temp5[0];
  lastSensorsData.temp6[1] = lastSensorsData.temp6[0];

  // get temps
  lastSensorsData.temp1[0] = sensors.getTempC(electricBoilerThermometer);
  lastSensorsData.temp2[0] = sensors.getTempC(gasBoilerThermometer);
  lastSensorsData.temp3[0] = sensors.getTempC(pumpPipeThermometer);
  lastSensorsData.temp4[0] = sensors.getTempC(outsideThermometer);
  lastSensorsData.temp5[0] = sensors.getTempC(energyPalThermometer);
  lastSensorsData.temp6[0] = sensors.getTempC(gasHeaterOut);

  //get measurements timestamp
  lastSensorsData.timestamp[0] = rtc.now().unixtime();
  actualMeasurement.timestamp = lastSensorsData.timestamp[0];

  // apply median filter
  actualMeasurement.temp1 = median(lastSensorsData.temp1, 3);
  actualMeasurement.temp2 = median(lastSensorsData.temp2, 3);
  actualMeasurement.temp3 = median(lastSensorsData.temp3, 3);
  actualMeasurement.temp4 = median(lastSensorsData.temp4, 3);
  actualMeasurement.temp5 = median(lastSensorsData.temp5, 3);
  actualMeasurement.temp6 = median(lastSensorsData.temp6, 3);
}

// get JsonObject with newest measurement and actual timestamp
void getMeasurementObject(JsonObject &destination){
  destination["timestamp"] = actualMeasurement.timestamp;
  destination["temp1"] = actualMeasurement.temp1;
  destination["temp2"] = actualMeasurement.temp2;
  destination["temp3"] = actualMeasurement.temp3;
  destination["temp4"] = actualMeasurement.temp4;
  destination["temp5"] = actualMeasurement.temp5;
  destination["temp6"] = actualMeasurement.temp6;
}

void handleMeasuring(){
  // get measurement
  JsonDocument measurementDoc;
  JsonObject measurementObject = measurementDoc.to<JsonObject>();
  takeMeasurement();
  getMeasurementObject(measurementObject);
  sendMeasurements();
  // automaticly turn on pump
  if(digitalRead(pin_OUT_1) == LOW){
    if((float(measurementObject["temp1"]) - float(measurementObject["temp2"])) >= PUMP_TEMP_DIFFERENCE_TRIG){
      Serial.println("[CONTROL] Pump on.");
      digitalWrite(pin_OUT_1, HIGH);
      lastPumpOn = rtc.now();
      checkStatesForChanges();
    }
  }
}