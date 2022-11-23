#include "LightSensorImpl.h"
#include <Arduino.h>

#define TH 320

LightSensorImpl::LightSensorImpl(int pin){
    this->pin = pin;
}

bool LightSensorImpl::isDark(){
    int value = analogRead(pin);
    return value < TH;
};