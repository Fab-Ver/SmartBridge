#include "LightSensorImpl.h"
#include <Arduino.h>

LighSensorImpl::LighSensorImpl(int pin){
    this->pin = pin;
}

int LighSensorImpl::getIntensity(){
    int value = analogRead(pin);
    return map(value,0,1000,0,255);
};