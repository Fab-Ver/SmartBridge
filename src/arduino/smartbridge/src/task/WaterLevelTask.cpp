#include "WaterLevelTask.h"
#include "msg/MsgService.h"
#include "util.h"
#include <Arduino.h>

#define WL1 0.25
#define WL2 0.15
#define WL_MAX 0.02
#define DEBOUNCE_DELAY 500
#define METERS_COV 100

int periods[4];
bool remoteControl = false;
int lastRemoteAngle;
unsigned long last_interrupt_time = 0;


WaterLevelTask::WaterLevelTask(int trigPin, int echoPin, int valvePin, int potPin, int greenPin, int redPin, Task* slt, Task* bt){
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->valvePin = valvePin;
    this->potPin = potPin;
    this->greenPin = greenPin;
    this->redPin = redPin;
    this->slTask = slt;
    this->blinktask = bt;
}

void WaterLevelTask::init(int normalPeriod, int preAlarmPeriod, int alarmPeriod){
    periods[NORMAL] = normalPeriod;
    periods[PRE_ALARM] = preAlarmPeriod;
    periods[ALARM] = alarmPeriod;
    periods[MANUAL] = alarmPeriod;
    currState = NORMAL;
    Task::init(getCurrentPeriod());
    Task::setActive(true);
    greenLed = new Led(greenPin);
    redLed = new Led(redPin);
    wlSensor = new WaterLevelSensor(trigPin,echoPin);
    valve = new Valve(valvePin);
    pot = new PotentiometerImpl(potPin);
    lcdMonitor = new LcdImpl();
}

void WaterLevelTask::tick(){
    int manualAngle;
    if(MsgService.isMsgAvailable()){
        Msg* msg = MsgService.receiveMsg();
        String content = msg->getContent();
        delete msg;
        if(isNumber(content)){
            manualAngle = content.toInt();
            lastRemoteAngle = manualAngle;
        } else {
            if(content == "MANUAL_ON"){
                currState = MANUAL;
                remoteControl = true;
            } else if (content == "MANUAL_OFF"){
                currState = ALARM;
                remoteControl = false;
            }
        }
    } else {
        if(!remoteControl){
            manualAngle = pot->getAngle();
        } else {
            manualAngle = lastRemoteAngle;
        }  
    }
        
    float currWL = wlSensor->getDistance();

    switch(currState){
        case NORMAL:{
            if(switchAndCheckState(currWL)){
                lcdMonitor->off();
                greenLed->switchOn();
                redLed->switchOff();
                MsgService.sendMsg("NORMAL "+ (String) currWL);
            } else {
                greenLed->switchOff();
            }
        }break;
        case PRE_ALARM:{
            if(switchAndCheckState(currWL)){
                if(!blinktask->isActive()){
                    blinktask->setActive(true);
                }
                lcdMonitor->on();
                lcdMonitor->writePreAlarm("PRE-ALARM",currWL);
                MsgService.sendMsg("PRE-ALARM "+ (String) currWL);
            } else {
                blinktask->updateState();
            }
        }break;
        case ALARM:{
            int angle = map(currWL,WL_MAX,WL2,180,0);
            if(switchAndCheckState(currWL)){
                greenLed->switchOff();
                redLed->switchOn();
                if(slTask->isActive()){
                    slTask->updateState();
                }
                lcdMonitor->on();
                valve->on();
                valve->setPosition(angle);
                lcdMonitor->writeAlarm("ALARM",currWL,angle);
                MsgService.sendMsg("ALARM "+ (String) currWL);
            } else {
                valve->off();
                redLed->switchOff();
                slTask->setActive(true);
            }
        } break;
        case MANUAL: {
            greenLed->switchOff();
            redLed->switchOn();
            if(slTask->isActive()){
                slTask->updateState();
            }
            lcdMonitor->on();
            valve->on();
            valve->setPosition(manualAngle);
            lcdMonitor->writeAlarm("ALARM - MANUAL ON",currWL,manualAngle);
            MsgService.sendMsg("MANUAL "+ (String) currWL);
        }break;
    }
}

int WaterLevelTask::getCurrentPeriod(){
    return periods[currState];
}

bool WaterLevelTask::switchAndCheckState(float currWL){
    noInterrupts();
    WLState prevState = currState;
    if(currWL > WL1){
        currState = NORMAL;
    } else if (currWL <= WL1 && currWL > WL2){
        currState = PRE_ALARM;
    } else if (currWL <= WL2 && currWL >= WL_MAX){
        currState = ALARM;
    }
    Task::setPeriod(getCurrentPeriod());
    interrupts();
    return prevState == currState;
}

void WaterLevelTask::updateState(){
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > DEBOUNCE_DELAY) {
        if(currState == ALARM){
            currState = MANUAL;
        } else if (currState == MANUAL){
            currState = ALARM;
        }
        Task::setPeriod(getCurrentPeriod());
    }
    last_interrupt_time = interrupt_time;
}
