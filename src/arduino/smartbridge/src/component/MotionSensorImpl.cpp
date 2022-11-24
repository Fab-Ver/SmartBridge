#include "MotionSensorImpl.h"
#include <Arduino.h>

#define CALIBRATION_TIME_SEC 20

MotionSensorImpl::MotionSensorImpl(int pin){
    this->pin = pin;
    pinMode(pin,INPUT);
    this->detectedStatus = false;
    Serial.print("Calibrating motion sensor");
    for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
        Serial.print(".");
        delay(1000);
    }
    Serial.println("done.");
    delay(50);
}

bool MotionSensorImpl::isDetected(){
    int current = digitalRead(pin);
    if(current != detectedStatus){
        detectedStatus = current;
    }
    return detectedStatus;
}