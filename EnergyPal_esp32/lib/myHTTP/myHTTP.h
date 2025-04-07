#ifndef MYHTTP_H
#define MYHTTP_H

#include <Arduino.h>

struct HttpRequestData{
    unsigned long unixTimestamp;
    String code;
    float value;
};


class myHTTP{
    public:
    myHTTP(const char* serverName);
    int sendPOSTrequest(String payload);
    private:
    const char* serverURL;
};

#endif