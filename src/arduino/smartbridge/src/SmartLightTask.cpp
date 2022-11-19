#include "SmartLightTask.h"
//#include <Arduino.h>

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
    state = OFF;
}

void SmartLightTask::tick(){
  switch (state){
  case OFF:
    break;
  case ON:
    break;
  }
};