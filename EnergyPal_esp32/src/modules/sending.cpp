#include "modules/sending.h"
#include "config.h"
#include "globals.h"
#include "modules/states.h"
#include "modules/measurements.h"
#include "myJsonStorage.h"
#include "myHTTP.h"
#include "myWifi.h"
#include <Arduino.h>
#include <ArduinoJson.h>

// add all unsent JsonObjects from myJsonStorage to the destination JsonArray
// return number of added objects
static int addUnsent(myJsonStorage storage, JsonArray destination){
    if(!storage.isEmpty()){
      int numAdded = 0;
      int numStored = storage.numStored();
      int num = 0;
      String* stored;
      if(numStored > LIMIT_UNSENT_IN_PAYLOAD){
        num = LIMIT_UNSENT_IN_PAYLOAD;
      } else {
        num = numStored;
      }
      stored = new String[num];
      storage.getJsonStrings(num, stored);
      for(int i = 0; i<num; i++){
        String jsonString = stored[i];
        JsonDocument doc;
        deserializeJson(doc, jsonString);
        JsonObject object = doc.as<JsonObject>();
        destination.add(object);
        numAdded++;
      }
      delete[] stored;
      return numAdded;
    } else {
      return 0;
    }
}
  
// send all data (latest data and data from the storage) to the server
// return response code
static int sendData(JsonObject latestData, myJsonStorage &storage, myHTTP httpClient){
    // create json document and array for the payload
    JsonDocument* payloadDoc = new JsonDocument;
    JsonArray payloadArray = payloadDoc->to<JsonArray>();
    if(wifi.connected()){
      int numAdded = addUnsent(storage, payloadArray); // add all unsent data to the payload
      payloadArray.add(latestData); // add latest data to the payload
      // serialize payload
      String* payload = new String;
      serializeJson(*payloadDoc, *payload);
      int httpResponseCode = httpClient.sendPOSTrequest(*payload);
      delete payload;
      delete payloadDoc;
      if(httpResponseCode > 0){
        storage.deleteJsonStrings(numAdded); // delete all sent data from the storage
        String msg = "Failed to send data with response code " + httpResponseCode;
        msg += ".";
        return httpResponseCode;
      } else {
        // save unsent data to the json storage
        String unsent;
        serializeJson(latestData, unsent);
        storage.storeJsonString(unsent);
        String msg = "Failed to send data with response code " + httpResponseCode;
        msg += ". Data has been saved to the storage.";
        return httpResponseCode;
      }
    } else {
      // save unsent data to the json storage
      String unsent;
      serializeJson(latestData, unsent);
      storage.storeJsonString(unsent);
      return -1;
    }
}

// send measured data to the server
void sendMeasurements(){
    int numToSend;
    if(unsentMeasurements.numStored()>LIMIT_UNSENT_IN_PAYLOAD){
      numToSend = LIMIT_UNSENT_IN_PAYLOAD+1;
    } else {
      numToSend = unsentMeasurements.numStored()+1;
    }
    Serial.print("Sending ");
    Serial.print(numToSend);
    Serial.print("/");
    Serial.print((unsentMeasurements.numStored()+1));
    Serial.print(" measurement/s... ");
    JsonDocument measurementDoc;
    JsonObject measurementObject = measurementDoc.to<JsonObject>();
    getMeasurementObject(measurementObject);
    int responseCode = sendData(measurementObject, unsentMeasurements, httpMeasurements);
    if(responseCode > 0){
      Serial.print("Sent with response code ");
      Serial.println(responseCode);
    } else {
      Serial.print("Failed to send the data with response code ");
      Serial.print(responseCode);
      Serial.println(". Unsent data has been saved to the storage.");
    }
}
  
// send actual I/O states to the server
void sendStates(){
    int numToSend;
    if(unsentStates.numStored()>LIMIT_UNSENT_IN_PAYLOAD){
      numToSend = LIMIT_UNSENT_IN_PAYLOAD+1;
    } else {
      numToSend = unsentStates.numStored()+1;
    }
    Serial.print("Sending ");
    Serial.print(numToSend);
    Serial.print("/");
    Serial.print((unsentStates.numStored()+1));
    Serial.print(" state/s... ");
    JsonDocument statesDoc;
    JsonObject statesObject = statesDoc.to<JsonObject>();
    getStatesObject(statesObject);
    int responseCode = sendData(statesObject, unsentStates, httpStates);
    if(responseCode > 0){
      Serial.print("Sent with response code ");
      Serial.println(responseCode);
    } else {
      Serial.print("Failed to send the data with response code ");
      Serial.print(responseCode);
      Serial.println(". Unsent data has been saved to the storage.");
    }
  }
  