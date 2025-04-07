#include "time.h"
#include "globals.h"
#include "myWiFi.h"
#include <Arduino.h>
#include <NTPClient.h>
#include <RTClib.h>

// sync RTC with NTP server
void syncTime(){
    Serial.print("Synchronizing RTC time... ");
    if(wifi.connected()){
      bool success = timeClient.update();
      if(success){
        unsigned long unixEpoch = timeClient.getEpochTime();
        rtc.adjust(DateTime(unixEpoch));
        Serial.print("Done. Actual RTC datetime: ");
        DateTime now = rtc.now();
        char buffer[22] = "DD. MM. YYYY hh:mm:ss";
        Serial.println(now.toString(buffer));
      } else {
        Serial.println("Failed to sync RTC. NTP update failed.");
      }
    } else {
      Serial.println("Failed to sync RTC. WiFi not connected.");
    }
  }