#include "SmartLightTask.h"
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
    currState = OFF;
}

void SmartLightTask::tick(){
  int start;
  ms->updateStatus();
  switch (currState){
  case OFF:
    if(ms->getStatus() && ls->getIntensity() < TH){
      led->switchOn();
      start = millis();
      currState = ON;
    }
    break;
  case ON:
    if((ms->getStatus() && millis() - start >= TIME_OFF) || ls->getIntensity() > TH){
      led->switchOff();
      currState = OFF;
    }
    break;
  }
};