#include "BlinkTask.h"
#include "SmartLightTask.h"
#include "WaterLevelTask.h"
#include "Scheduler.h"
#include "config.h"
#include "MsgService.h"
#include <EnableInterrupt.h>
#include <Arduino.h>

Scheduler sched;
WaterLevelTask* wlt;

void buttonHandler(){
  wlt->updateState();
}

void setup() {
  MsgService.init();
  
  sched.init(100);

  Task* bt = new BlinkTask(LC_PIN);
  bt->init(BLINK_PERIOD);

  Task* slt = new SmartLightTask(LA_PIN,PHORES_PIN,PIR_PIN);
  slt->init(SMART_LIGHT_PERIOD);

  wlt = new WaterLevelTask(TRIG_PIN,ECHO_PIN,SERVO_PIN,POT_PIN,LB_PIN,LC_PIN,slt,bt);
  wlt->init(WATER_LEVEL_NORMAL_PERIOD,WATER_LEVEL_PREALARM_PERIOD,WATER_LEVEL_ALARM_PERIOD);

  enableInterrupt(BUTTON_PIN,buttonHandler,CHANGE);

  sched.addTask(bt);
  sched.addTask(slt);
  sched.addTask(wlt);
}

void loop() {
  sched.schedule();
}
