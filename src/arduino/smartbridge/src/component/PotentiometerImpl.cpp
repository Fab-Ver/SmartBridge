#include "PotentiometerImpl.h"
#include "Arduino.h"

PotentiometerImpl::PotentiometerImpl(int pin){
    this->pin = pin;
}

int PotentiometerImpl::getAngle(){
    int value = analogRead(pin);
    return map(value,0,1024,0,180);
}