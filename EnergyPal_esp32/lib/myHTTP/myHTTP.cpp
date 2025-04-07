#include "myHTTP.h"
#include <HTTPClient.h>
#include <Arduino.h>

myHTTP::myHTTP(const char* url) : serverURL(url){
} 

// send HTTP POST request with payload to the server
int myHTTP::sendPOSTrequest(String payload){
    // create HTTPClient object
    HTTPClient http;
    // begin the HTTP connection
    http.begin(serverURL);
    // specify content type
    http.addHeader("Content-Type", "application/json");
    // send HTTP POST request
    int httpResponseCode = http.POST(payload);
    // end the HTTP connection
    http.end();
    return httpResponseCode;
}