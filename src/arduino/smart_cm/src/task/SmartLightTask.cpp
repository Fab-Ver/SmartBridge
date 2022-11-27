#include "SmartLightTask.h"
#include <Arduino.h>
#include "MsgService.h"

#define TIME_OFF 5000

int lastON = 0;

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
    MsgService.sendMsg("LED_OFF");
}

void SmartLightTask::tick(){
  bool detected = ms->isDetected();
  bool dark = ls->isDark();

  switch (currState){
    case LIGHT_OFF: {
      if(detected && dark){
        MsgService.sendMsg("LED_ON");
        currState = LIGHT_ON;
      }
      led->switchOff();
    }break;
    case LIGHT_ON:{
      lastON = millis();
      if(!dark){
        currState = LIGHT_OFF;
        MsgService.sendMsg("LED_OFF");
      } else if (dark && !detected){
        currState = WAITING;
      }
      led->switchOn();
    }break;
    case WAITING:{
      if(dark && detected){
        currState = LIGHT_ON;
        MsgService.sendMsg("LED_ON");
      } else {
        if((millis() - lastON >= TIME_OFF) || !dark){
          currState = LIGHT_OFF;
          MsgService.sendMsg("LED_OFF");
        }
      }
    }break;
    case SYS_OFF:{
      led->switchOff();
      MsgService.sendMsg("SYS_OFF");
      currState = LIGHT_OFF;
      Task::setActive(false);
    }break;
  }
}

void SmartLightTask::updateState(){
    currState = SYS_OFF;
}