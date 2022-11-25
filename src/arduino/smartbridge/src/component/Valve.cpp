#include "Valve.h"
#include "Arduino.h"

#define CLOSE 0

Valve::Valve(int pin){
    this->pin = pin;
}

void Valve::on(){
    if(!motor.attached()){
        motor.attach(pin);
    }
}

void Valve::off(){
    if(motor.attached()){
        this->setPosition(CLOSE);
        motor.detach();
    }
}

void Valve::setPosition(int angle){
    float coef = ((float)(MAX_PULSE_WIDTH - MIN_PULSE_WIDTH))/180.0;
    motor.write(MIN_PULSE_WIDTH + angle * coef);
};