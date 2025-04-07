#include "config.h"
#include <stdint.h>
#include <DallasTemperature.h>

// user file with credentials
#include "credentials.h"

// declare ID of this device
const char* ENERGYPAL_ID = user_ENERGYPAL_ID;

// WiFi connection info
const char* WIFI_SSID = user_WIFI_SSID;
const char* WIFI_PASSWORD = user_WIFI_PASSWORD;

// website data handler URL
const char* MEASUREMENTS_HANDLER_URL = user_MEASUREMENTS_HANDLER_URL;
const char* STATES_HANDLER_URL = user_STATES_HANDLER_URL;

// web socket connection info
const char* WS_HOST = user_WS_HOST;
const char* WS_PATH = user_WS_PATH;
const uint16_t WS_PORT = 443;

// declare sensors addrresses
const DeviceAddress electricBoilerThermometer = { 0x28, 0xA2, 0x08, 0x0B, 0x17, 0x13, 0x01, 0x51 }; 
const DeviceAddress gasBoilerThermometer = { 0x28, 0x4A, 0x0F, 0x76, 0xE0, 0x01, 0x3C, 0x74 };
const DeviceAddress outsideThermometer = { 0x28, 0xFF, 0xEF, 0x84, 0x73, 0x15, 0x02, 0x8E };
const DeviceAddress energyPalThermometer = { 0x28, 0x9F, 0xA1, 0x89, 0x34, 0x21, 0x01, 0x24 }; // { 0x28, 0x41, 0xD9, 0x37, 0x34, 0x21, 0x01, 0x24 };
const DeviceAddress pumpPipeThermometer = { 0x28, 0x8D, 0x98, 0x19, 0x0D, 0x00, 0x00, 0x8C };
const DeviceAddress gasHeaterOut = { 0x28, 0x89, 0x29, 0x4F, 0x34, 0x21, 0x01, 0x08 };