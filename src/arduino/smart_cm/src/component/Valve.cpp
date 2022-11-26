#include "Valve.h"
#include "Arduino.h"

#define CLOSE 0

Valve::Valve(int pin){
    motor.attach(pin);
}

void Valve::close(){
        this->setPosition(CLOSE);
}

void Valve::setPosition(int angle){
    float coef = ((float)(MAX_PULSE_WIDTH - MIN_PULSE_WIDTH))/180.0;
    motor.write(MIN_PULSE_WIDTH + angle * coef);
};