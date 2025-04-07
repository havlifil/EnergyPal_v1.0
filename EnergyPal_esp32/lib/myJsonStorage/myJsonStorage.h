#ifndef MYJSONSTORAGE_H
#define MYJSONSTORAGE_H

#include <Arduino.h>

class myJsonStorage{
    public:
    myJsonStorage(const char* dir);
    bool begin();
    int storeJsonString(String jsonString);
    void getJsonStrings(int num, String* destination);
    int deleteJsonStrings(int num);
    bool isEmpty();
    int numStored();
    void printAll();
    private:
    const char* dir;
    int numStrings = 0;
};

#endif