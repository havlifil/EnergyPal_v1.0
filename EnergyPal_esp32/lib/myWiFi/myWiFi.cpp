#include "myWiFi.h"
#include <WiFi.h>

myWiFi::myWiFi(){
}

bool myWiFi::connect(const char* ssid, const char* password, int timeoutMiliseconds){
    // begin the wifi connection
    WiFi.begin(ssid, password);
    // check if the wifi is connected until timeout
    int time = 0;
    while(time<timeoutMiliseconds){
        if(WiFi.status() == WL_CONNECTED){
            return true;
        }
        delay(100);
        time += 100;
    }
    // if connecting fails disconnects wifi
    WiFi.disconnect();
    return false;
}

void myWiFi::disconnect(){
    // disconnect wifi
    WiFi.disconnect();
}

bool myWiFi::connected(){
    // check if wifi is connected
    if(WiFi.status() == WL_CONNECTED){
        return true;
    } else {
        return false;
    }
}