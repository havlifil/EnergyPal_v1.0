#include "modules/math.h"
#include <Arduino.h>
#include <algorithm>
#include <cmath>
using namespace std;

// get median from dataset
float median(float *dataset, int size){
    if(size == 0){
        return 0.0f;
    }

    float arr[size];

    for(int i = 0; i < size; i++){
        arr[i] = dataset[i];
    }

    sort(arr, arr + size - 1);

    if((size % 2) == 0){
        return (arr[(size/2) - 1] + arr[size/2]) / 2.0f;
    } else {
        return arr[size/2];
    }
}

float roundToTwoDecimals(float value){
    return roundf(value * 100) / 100;
}