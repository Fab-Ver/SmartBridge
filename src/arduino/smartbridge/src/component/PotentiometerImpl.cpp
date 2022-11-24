#include "PotentiometerImpl.h"
#include "Arduino.h"

PotentiometerImpl::PotentiometerImpl(int pin){
    this->pin = pin;
}

int PotentiometerImpl::getAngle(){
    int value = analogRead(pin);
    /*Map the value from analog values range 0-1024 to angle range 0-180*/
    return map(value,0,1024,0,180);
}