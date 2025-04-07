#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

#include <stdint.h>
#include <ArduinoJson.h>

struct LastSensorsData{
    uint32_t timestamp[3]; 
    float temp1[3];
    float temp2[3];
    float temp3[3];
    float temp4[3];
    float temp5[3];
    float temp6[3];
};

struct Measurement{
    uint32_t timestamp;
    float temp1;
    float temp2;
    float temp3;
    float temp4;
    float temp5;
    float temp6;
};

void takeMeasurement(); // shift global arrays of last measurements and take new measurement
void getMeasurementObject(JsonObject &destination); // return JsonObject with newest measurement and actual timestamp
void handleMeasuring(); // handles whole measuring process

#endif