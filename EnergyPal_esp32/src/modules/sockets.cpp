#include "globals.h"
#include "config.h"
#include "modules/sockets.h"
#include "modules/commands.h"
#include <ArduinoJson.h>

// handle WebSocket events
void webSocketEvent(WStype_t type, uint8_t* payload, size_t lenght) {
    switch(type){
      case WStype_DISCONNECTED:
        Serial.println("WebSocket event: DISCONNECTED");
        break;
      case WStype_CONNECTED:
        Serial.println("WebSocket event: CONNECTED");
        break;
      case WStype_TEXT:{
        Serial.println("WebSocket event: RECEIVED TEXT");
        JsonDocument payloadDoc;
        DeserializationError error = deserializeJson(payloadDoc, payload, lenght);
        if(error) {
          Serial.print("JSON parse error: ");
          Serial.println(error.c_str());
        } else {
          if(ENERGYPAL_ID == payloadDoc["deviceID"]){
            String operation = payloadDoc["operation"];
            int value = payloadDoc["value"];
            Serial.print("RECEIVED TEXT: operation: ");
            Serial.print(operation);
            Serial.print(" value: ");
            Serial.println(value);
            executeServerCommand(operation, value);
          } else {
            Serial.println("RECEIVED TEXT: Device ID doesn't match.");
          }
        }
  
      }
        break;
      case WStype_ERROR:
        Serial.println("WebSocketEvent: ERROR");
        break;
      case WStype_BIN:
        Serial.println("WebSocketEvent: RECEIVED BINARY (not handled)");
        break;
      default:
        Serial.println("WebSocketEvent: INVALID EVENT");
        break;
    }
  }

// check for WebSocket events
void checkWebSocket(){
    socket.loop();
}