#include "WaterLevelTask.h"
#include <Arduino.h>

#define WL1 3
#define WL2 5
#define WL_MAX 7

int periods[3];

WaterLevelTask::WaterLevelTask(int trigPin, int echoPin, int valvePin, int potPin, int greenPin, int redPin, int buttonPin, SmartLightTask* slt, BlinkTask* bt){
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->valvePin = valvePin;
    this->potPin = potPin;
    this->greenPin = greenPin;
    this->redPin = redPin;
    this->buttonPin = buttonPin;
    this->slTask = slt;
    this->blinktask = bt;
}

void WaterLevelTask::init(int normalPeriod, int preAlarmPeriod, int alarmPeriod){
    periods[NORMAL] = normalPeriod;
    periods[PRE_ALARM] = preAlarmPeriod;
    periods[ALARM] = alarmPeriod;
    currState = NORMAL;
    Task::init(getPeriod());
    Task::setActive(true);
    greenLed = new Led(greenPin);
    redLed = new Led(redPin);
    wlSensor = new WaterLevelSensor(trigPin,echoPin);
    valve = new Valve(valvePin);
    pot = new PotentiometerImpl(potPin);
    lcdMonitor = new LcdImpl();
}

void WaterLevelTask::tick(){
    float currWL = wlSensor->getDistance();
    switch (currState){
    case NORMAL:
        if(switchAndCheckState(currWL)){
            lcdMonitor->off();
            greenLed->switchOn();
            redLed->switchOff();
        } else {
            greenLed->switchOff();
        }
        break;
    case PRE_ALARM:
        if(switchAndCheckState(currWL)){
            blinktask->setActive(true);
            lcdMonitor->on();
            lcdMonitor->writePreAlarm("PRE-ALARM",currWL);
        } else {
            blinktask->setState(FSM_OFF);
        }
        break;
    case ALARM:
        int angle = map(currWL,WL2,WL_MAX,0,180);
        if(switchAndCheckState(currWL)){
            greenLed->switchOff();
            redLed->switchOn();
            slTask->setActive(false); //Riguardare questa linea di codice
            lcdMonitor->on();
            valve->on();
            valve->setPosition(angle);
            lcdMonitor->writeAlarm("ALARM",currWL,angle);
        } else {
            slTask->setActive(true);
            redLed->switchOff();
            valve->off();
        }
        break;
    case MANUAL:
        break;
    }
}

int WaterLevelTask::getPeriod(){
    return periods[currState];
}

bool WaterLevelTask::switchAndCheckState(float currWL){
    noInterrupts();
    WLState prevState = currState;
    if(currWL < WL1){
        currState = NORMAL;
    } else if (currWL >= WL1 && currWL < WL2){
        currState = PRE_ALARM;
    } else if (currWL >= WL2 && currWL <= WL_MAX){
        currState = ALARM;
    }
    Task::setPeriod(getPeriod());
    interrupts();
    return prevState == currState;
};