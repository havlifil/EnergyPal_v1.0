#ifndef STATES_H
#define STATES_H

#include <ArduinoJson.h>

struct States{
    bool IN_1 = false;
    bool IN_2 = false;
    bool IN_3 = false;
    bool IN_4 = false;
    bool IN_5 = false;
    bool IN_6 = false;
    bool OUT_1 = false;
    bool OUT_2 = false;
    bool OUT_3 = false;
    bool OUT_4 = false;
};

void getStatesObject(JsonObject &destination); // return JsonObject with actual I/O states and actual timestamp
void checkStatesForChanges(); // check states for changes and send changes to the server

#endif