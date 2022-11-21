#include "SmartLightTask.h"
#include "config.h"
#include <Arduino.h>

#define TH 100
#define TIME_OFF 5000

SmartLightTask::SmartLightTask(int ledPin, int lsPin, int msPin){
    this->ledPin = ledPin;
    this->lsPin = lsPin;
    this->msPin = msPin;
}

void SmartLightTask::init(int period){
    Task::init(period);
    Task::setActive(true);
    led = new Led(ledPin);
    ls = new LighSensorImpl(lsPin);
    ms = new MotionSensorImpl(msPin);
    currState = LIGHT_OFF;
}

void SmartLightTask::tick(){
  int start;
  bool detected = ms->updateStatus();
  int lightIntensity = ls->getIntensity();
  switch (currState){
  case LIGHT_OFF:
    if(detected && lightIntensity < TH){
      led->switchOn();
      start = millis();
      currState = LIGHT_ON;
    }
    break;
  case LIGHT_ON:
    if((detected && millis() - start >= TIME_OFF) || lightIntensity > TH){
      led->switchOff();
      currState = LIGHT_OFF;
    }
    break;
  case FSM_OFF:
    led->switchOff();
    Task::setActive(false);
    currState = LIGHT_OFF;
  }
}

void SmartLightTask::setState(State state){
    noInterrupts();
    this->currState = state;
    interrupts();
}