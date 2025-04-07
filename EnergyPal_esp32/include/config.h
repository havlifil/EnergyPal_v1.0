#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <DallasTemperature.h>

// declare ID of this device
extern const char* ENERGYPAL_ID;

// WiFi connection info
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

// website data handler URL
extern const char* MEASUREMENTS_HANDLER_URL;
extern const char* STATES_HANDLER_URL;

// web socket connection info
extern const char* WS_HOST;
extern const char* WS_PATH;
extern const uint16_t WS_PORT;

// declare sensors addrresses
extern const DeviceAddress electricBoilerThermometer;
extern const DeviceAddress gasBoilerThermometer;
extern const DeviceAddress outsideThermometer;
extern const DeviceAddress energyPalThermometer;
extern const DeviceAddress pumpPipeThermometer;
extern const DeviceAddress gasHeaterOut;

// define ESP-WROOM-32 pins
#define pin_IN_1 32
#define pin_IN_2 33
#define pin_IN_3 25
#define pin_IN_4 26
#define pin_IN_5 23
#define pin_IN_6 22
#define pin_OUT_1 21
#define pin_OUT_2 19
#define pin_OUT_3 18
#define pin_OUT_4 17
#define pin_SDA 16
#define pin_SCL 4
#define pin_DQ 13

#define WIFI_TIMEOUT 5000 // define wifi timeout [ms]
#define UDP_PORT 9999 // define UDP port

#define LIMIT_UNSENT_IN_PAYLOAD 100 // limit how much unsent data could be added to the payload (prevent memory overflow)
#define PUMP_TEMP_DIFFERENCE_TRIG 5.0f // difference between temperatures in electric and gas boiler, that triggers pump
#define PUMP_ON_DURATION 20*60 // duration in seconds of pump on states

#endif