#include "SmartLightTask.h"
#include <Arduino.h>
#include "msg/MsgService.h"

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
    ls = new LightSensorImpl(lsPin);
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
      MsgService.sendMsg("LED_ON");
      start = millis();
      currState = LIGHT_ON;
    }
    break;
  case LIGHT_ON:
    if((detected && (millis() - start >= TIME_OFF)) || lightIntensity > TH){
      led->switchOff();
      MsgService.sendMsg("LED_OFF");
      currState = LIGHT_OFF;
    }
    break;
  case FSM_OFF:
    led->switchOff();
    MsgService.sendMsg("SYSTEM_AND_LED_OFF");
    Task::setActive(false);
    currState = LIGHT_OFF;
    break;
  }
}

void SmartLightTask::updateState(){
    currState = FSM_OFF;
}