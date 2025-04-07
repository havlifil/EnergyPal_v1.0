#ifndef GLOBALS_H
#define GLOBALS_H

#include <RTClib.h>
#include "modules/measurements.h"
#include "modules/states.h"

class DateTime;
class myWiFi;
class WiFiUDP;
class myJsonStorage;
class DallasTemperature;
class RTC_DS3231;
class NTPClient;
class WebSocketsClient;
class myHTTP;

// states
extern States states;

// measurements
extern LastSensorsData lastSensorsData;
extern Measurement actualMeasurement;

// pump
extern DateTime lastPumpOn;

// wifi globals
extern myWiFi wifi;
extern WiFiUDP udp;

// json storage
extern myJsonStorage unsentMeasurements;
extern myJsonStorage unsentStates;

// sensors
extern DallasTemperature sensors;

// RTC
extern RTC_DS3231 rtc;

// NTP time client
extern NTPClient timeClient;

// Websocket client
extern WebSocketsClient socket;

// HTTP clients
extern myHTTP httpMeasurements; // HTTP client for sending data
extern myHTTP httpStates; // HTTP client for sending states

#endif