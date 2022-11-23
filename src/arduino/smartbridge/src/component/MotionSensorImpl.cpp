#include "MotionSensorImpl.h"
#include <Arduino.h>

#define CALIBRATION_TIME_SEC 5

MotionSensorImpl::MotionSensorImpl(int pin){
    this->pin = pin;
    pinMode(pin,INPUT);
    detectedStatus = false;
    Serial.print("Calibrating motion sensor... ");
    for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" Motion sensor ready.");
    delay(50);
}

bool MotionSensorImpl::updateStatus(){
    int current = digitalRead(pin);
    if(current != detectedStatus){
        detectedStatus = current;
    }
    return detectedStatus;
}