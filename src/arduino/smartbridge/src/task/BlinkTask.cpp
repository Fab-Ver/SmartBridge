#include "BlinkTask.h"
#include <Arduino.h>

BlinkTask::BlinkTask(int pin){
    this->pin = pin;
}

void BlinkTask::init(int period){
    Task::init(period);
    Task::setActive(false);
    led = new Led(pin);
    currState = OFF;
}

void BlinkTask::tick(){
    switch (currState){
    case OFF:
      led->switchOn();
      currState = ON; 
      break;
    case ON:
      led->switchOff();
      currState = OFF;
      break;
    case BLINK_OFF:
        led->switchOff();
        Task::setActive(false);
        currState = OFF;
        break;
  }
}

void BlinkTask::updateState(){
    currState = BLINK_OFF;
}