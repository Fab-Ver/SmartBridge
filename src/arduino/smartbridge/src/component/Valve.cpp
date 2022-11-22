#include "Valve.h"
#include "Arduino.h"

Valve::Valve(int pin){
    this->pin = pin;
}

void Valve::on(){
    motor.attach(pin);
}

void Valve::off(){
    motor.detach();
}

void Valve::setPosition(int angle){
    float coef = ((float)(MAX_PULSE_WIDTH - MIN_PULSE_WIDTH))/180.0;
    motor.write(MIN_PULSE_WIDTH+angle*coef);
};