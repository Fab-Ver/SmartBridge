#include "BlinkTask.h"
#include <Arduino.h>

BlinkTask::BlinkTask(int pin){
    this->pin = pin;
}

void BlinkTask::init(int period){
    Task::init(period);
    Task::setActive(false);
    currState = LIGHT_OFF;
}

void BlinkTask::tick(){
    switch (currState){
    case LIGHT_OFF:
      led->switchOn();
      currState = LIGHT_ON; 
      break;
    case LIGHT_ON:
      led->switchOff();
      currState = LIGHT_OFF;
      break;
    case FSM_OFF:
        led->switchOff();
        Task::setActive(false);
        currState = LIGHT_OFF;
        break;
  }
}

void BlinkTask::setState(BTState state){
    this->currState = state;
}