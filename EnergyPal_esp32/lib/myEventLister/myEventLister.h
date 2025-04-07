#ifndef MYEVENTLISTER_H
#define MYEVENTLISTER_H

#include <vector>
using namespace std;
#include <RTClib.h>

typedef void (*FunctionPointer)();

class myEventLister{
    public:
    myEventLister();
    bool addRepeatedEvent(FunctionPointer function, int repeatTime);
    bool removeRepeatedEvent(FunctionPointer function);
    void loop();
    private:
    struct repeatedEvent{
        FunctionPointer function;
        int repeatTime;
        unsigned long lastCallTime;
    };
    struct Event{
        FunctionPointer function;
        DateTime datetime;
    };
    vector<repeatedEvent> repeatedEventList;
    vector<Event> eventList;
};

#endif