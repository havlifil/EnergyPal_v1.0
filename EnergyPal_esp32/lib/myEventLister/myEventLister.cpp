#include "myEventLister.h"
#include <Arduino.h>

myEventLister::myEventLister(){
}

bool myEventLister::addRepeatedEvent(FunctionPointer function, int repeatTime){
    for(int i = 0; i < repeatedEventList.size(); i++){
        if(repeatedEventList[i].function == function){
            return false;
        }
    }
    repeatedEvent event;
    event.function = function;
    event.repeatTime = repeatTime;
    event.lastCallTime = -1;
    repeatedEventList.push_back(event);
    return true;
}

bool myEventLister::removeRepeatedEvent(FunctionPointer function){
    bool removed = false;
    int listSize = repeatedEventList.size();
    for(int i = 0; (i < listSize) or (removed == false); i++){
        if(repeatedEventList[i].function == function){
            repeatedEventList.erase(repeatedEventList.begin() + i);
            removed = true;
        }
    }
    return removed;
}

void myEventLister::loop(){
    for(int i = 0; i < repeatedEventList.size(); i++){
        if(((millis() - repeatedEventList[i].lastCallTime) >= repeatedEventList[i].repeatTime) or (repeatedEventList[i].lastCallTime == -1)) {
            repeatedEventList[i].function();
            repeatedEventList[i].lastCallTime = millis();
        }
    }
}
