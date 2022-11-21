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
        greenLed->switchOn();
        redLed->switchOff();
        if(currWL >= WL1 && currWL < WL2){
            noInterrupts();
            currState = PRE_ALARM;
            interrupts();
        } else if (currWL >= WL2 && currWL <= WL_MAX){
            noInterrupts();
            currState = ALARM;
            interrupts();
        }
        break;
    case PRE_ALARM:
        
        break;
    case ALARM:
        break;
    case MANUAL:
        break;
    }
}

int WaterLevelTask::getPeriod(){
    return periods[currState];
}