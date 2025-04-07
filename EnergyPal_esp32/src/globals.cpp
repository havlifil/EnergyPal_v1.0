#include "globals.h"
#include "config.h"

#include "modules/states.h"
#include "modules/measurements.h"
#include "myWiFi.h"
#include "myJsonStorage.h"
#include "myHTTP.h"
#include <WiFi.h>
#include <RTClib.h>
#include <NTPClient.h>
#include <webSocketsClient.h>

// states
States states;

// measurements
LastSensorsData lastSensorsData;
Measurement actualMeasurement;

// pump
DateTime lastPumpOn;

// wifi globals
myWiFi wifi;
WiFiUDP udp;

// json storage
static const char* unsentMeasurementsDir = "/data/unsentMeasurements.txt";
myJsonStorage unsentMeasurements(unsentMeasurementsDir);
static const char* unsentStatesDir = "/data/unsentStates.txt";
myJsonStorage unsentStates(unsentStatesDir);

// sensors
static OneWire oneWire(pin_DQ);
DallasTemperature sensors(&oneWire);

// RTC
RTC_DS3231 rtc;

// NTP time client
NTPClient timeClient(udp, "europe.pool.ntp.org", 2*3600, 5*3600*1000); // offset +2 hours (CET), update interval 5 hours

// Websocket client
WebSocketsClient socket;

// HTTP clients
myHTTP httpMeasurements(MEASUREMENTS_HANDLER_URL); // HTTP client for sending data
myHTTP httpStates(STATES_HANDLER_URL); // HTTP client for sending states