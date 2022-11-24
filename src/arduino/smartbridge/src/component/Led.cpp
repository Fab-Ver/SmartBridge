#include "Led.h"
#include <Arduino.h>

int currState = LOW;

Led::Led(int pin){
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void Led::switchOn(){
    if(currState == LOW){
        digitalWrite(pin,HIGH);
        currState = HIGH;
    }
}

void Led::switchOff(){
    if(currState == HIGH){
        digitalWrite(pin,LOW);
        currState = LOW;
    }
};