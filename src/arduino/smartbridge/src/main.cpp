#include "BlinkTask.h"
#include "SmartLightTask.h"
#include "WaterLevelTask.h"
#include "Scheduler.h"
#include "config.h"
#include <EnableInterrupt.h>
#include <Arduino.h>


Scheduler sched;
Task* wlt;

void buttonHandler(){
  wlt->updateState();
}

void setup() {
  sched.init(0);

  Task* bt = new BlinkTask(LC_PIN);
  bt->init(0);

  Task* slt = new SmartLightTask(LA_PIN,PHORES_PIN,PIR_PIN);
  slt->init(0);

  wlt = new WaterLevelTask(TRIG_PIN,ECHO_PIN,SERVO_PIN,POT_PIN,LB_PIN,LC_PIN,0,slt,bt);
  wlt->init(0);

  enableInterrupt(BUTTON_PIN,buttonHandler,CHANGE);

  sched.addTask(bt);
  sched.addTask(slt);
  sched.addTask(wlt);
}

void loop() {
  sched.schedule();
}
