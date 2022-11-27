#include "LightSensorImpl.h"
#include <Arduino.h>

#define THRESHOLD 300

LightSensorImpl::LightSensorImpl(int pin){
    this->pin = pin;
}

bool LightSensorImpl::isDark(){
    return analogRead(pin) < THRESHOLD;
};