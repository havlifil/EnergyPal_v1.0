#include "myJsonStorage.h"
#include <Arduino.h>
#include <SPIFFS.h>
#include <FS.h>

myJsonStorage::myJsonStorage(const char* dir) : dir(dir){
}

// mount SPIFFS, if not already exist create new file for json storage
bool myJsonStorage::begin(){
    bool success = SPIFFS.begin(); // try to mount SPIFFS
    if(success){
        // if file doesn't already exist create new
        if(!SPIFFS.exists(dir)){
            File file = SPIFFS.open(dir, "w");
            // Add num of strings to the file (only for debuging)
            /*for(int i = 0; i<3000; i++){
                file.println("{\"timestamp\":1740684872,\"temp1\":5.61,\"temp2\":22.93,\"temp3\":28.28,\"temp4\":38.36}\n");
                numStrings++;
            }*/
            if(file){
                file.close();
                return true;
            } else {
                return false;
            }
        } else {
            File file = SPIFFS.open(dir, "r");
            if(file){
                while(file.available()){
                    String line = file.readStringUntil('\n');
                    numStrings++;
                }
                file.close();
                return true;
            } else {
                return false;
            }
        }
    } else {
        return false;
    }
}

// store json string in the storage
int myJsonStorage::storeJsonString(String jsonString){
    File file = SPIFFS.open(dir, "a"); // open storage file to append
    if(file){
        file.println(jsonString); // append new line with jsonString
        file.close();
        numStrings++;
        return numStrings;
    } else {
        return numStrings;
    }
}

// get num of json strings from start of the storage
void myJsonStorage::getJsonStrings(int num, String* destination){
    File file = SPIFFS.open(dir, "r"); // open storage file to read
    if(file){
        // get data from the file
        for(int i = 0; i < num; i++){
            if(file.available()){
                destination[i] = file.readStringUntil('\n');
            } else {
                destination[i] = "";
            }
        }
        file.close();
    }
}

// delete num of json strings from start of the storage
int myJsonStorage::deleteJsonStrings(int num){
    String originalFileDir = "/jsonStorage/originalFile.txt";
    bool success = SPIFFS.rename(dir, originalFileDir); // rename original file
    int numStored = 0;
    if(success){
        File newFile = SPIFFS.open(dir, "w"); // create new file for writing (new storage file)
        File originalFile = SPIFFS.open(originalFileDir, "r"); // open original file for reading
        if(newFile && originalFile){
            int line = 0; // current line
            String lineContent; // currents line content
            // copy all lines that shouln't be deleted to the new storage file
            while(originalFile.available()){
                lineContent = originalFile.readStringUntil('\n');
                if(line >= num){
                    newFile.println(lineContent);
                    numStored++;
                }
                line++;
            }
            originalFile.close();
            newFile.close();
            numStrings = numStored;
            SPIFFS.remove(originalFileDir); // remove original file
            return numStrings;
        } else {
            newFile.close();
            originalFile.close();
            SPIFFS.remove(originalFileDir); // remove original file
            return numStrings;
        }
    } else {
        return numStrings;
    }
}

// check if storage is empty
bool myJsonStorage::isEmpty(){
    if(numStrings == 0){
        return true;
    } else {
        return false;
    }
}

// return number of stored strings
int myJsonStorage::numStored(){
    return numStrings;
}

// print all stored strings to the Serial
void myJsonStorage::printAll(){
    File file = SPIFFS.open(dir, "r"); // open storage file for reading
    if(file){
        // print all data to the Serial
        Serial.println("Unsent data:");
        while(file.available()){
            Serial.println(file.readStringUntil('\n'));
        }
    } else {
        Serial.println("Failed to open storage file. Can't print all.");
    }
    file.close();
}