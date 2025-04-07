#include "modules/states.h"
#include "modules/sending.h"
#include "config.h"
#include "globals.h"

// return States struct with actual I/O states
static States getStates(){
    States states;
    states.IN_1 = digitalRead(pin_IN_1);
    states.IN_2 = digitalRead(pin_IN_2);
    states.IN_3 = digitalRead(pin_IN_3);
    states.IN_4 = digitalRead(pin_IN_4);
    states.IN_5 = digitalRead(pin_IN_5);
    states.IN_6 = digitalRead(pin_IN_6);
    states.OUT_1 = digitalRead(pin_OUT_1);
    states.OUT_2 = digitalRead(pin_OUT_2);
    states.OUT_3 = digitalRead(pin_OUT_3);
    states.OUT_4 = digitalRead(pin_OUT_4);
    return states;
}

// get JsonObject with actual I/O states and actual timestamp
void getStatesObject(JsonObject &destination){
    uint32_t timestamp = rtc.now().unixtime(); // get current unix timestamp
    destination["timestamp"] = timestamp;
    destination["IN_1"] = digitalRead(pin_IN_1);
    destination["IN_2"] = digitalRead(pin_IN_2);
    destination["IN_3"] = digitalRead(pin_IN_3);
    destination["IN_4"] = digitalRead(pin_IN_4);
    destination["IN_5"] = digitalRead(pin_IN_5);
    destination["IN_6"] = digitalRead(pin_IN_6);
    destination["OUT_1"] = digitalRead(pin_OUT_1);
    destination["OUT_2"] = digitalRead(pin_OUT_2);
    destination["OUT_3"] = digitalRead(pin_OUT_3);
    destination["OUT_4"] = digitalRead(pin_OUT_4);
}

// check states for changes and send changes to the server
void checkStatesForChanges(){
    States actualStates = getStates();
    if(
      (actualStates.IN_1 != states.IN_1) ||
      (actualStates.IN_2 != states.IN_2) ||
      (actualStates.IN_3 != states.IN_3) ||
      (actualStates.IN_4 != states.IN_4) ||
      (actualStates.IN_5 != states.IN_5) ||
      (actualStates.IN_6 != states.IN_6) ||
      (actualStates.OUT_1 != states.OUT_1) ||
      (actualStates.OUT_2 != states.OUT_2) ||
      (actualStates.OUT_3 != states.OUT_3) ||
      (actualStates.OUT_4 != states.OUT_4)
    ){
      states.IN_1 = actualStates.IN_1;
      states.IN_2 = actualStates.IN_2;
      states.IN_3 = actualStates.IN_3;
      states.IN_4 = actualStates.IN_4;
      states.IN_5 = actualStates.IN_5;
      states.IN_6 = actualStates.IN_6;
      states.OUT_1 = actualStates.OUT_1;
      states.OUT_2 = actualStates.OUT_2;
      states.OUT_3 = actualStates.OUT_3;
      states.OUT_4 = actualStates.OUT_4;
      sendStates();
    }
  }