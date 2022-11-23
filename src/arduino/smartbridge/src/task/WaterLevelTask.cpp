#include "WaterLevelTask.h"
#include "msg/MsgService.h"
#include "util.h"
#include <Arduino.h>

#define WL1 15
#define WL2 10
#define WL_MAX 1
#define DEBOUNCE_DELAY 500
#define METERS_COV 100

int periods[4];
int msg_millis = 0;
int pot_millis = 0;
int last_pot = 0;
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
    int msgAngle;
    if(MsgService.isMsgAvailable()){
        Msg* msg = MsgService.receiveMsg();
        if(isNumeric(msg->getContent())){
            msgAngle = msg->getContent().toInt();
            msg_millis = millis();
        } else {
            if(msg->getContent() == "MANUAL_ON"){
                noInterrupts();
                currState = MANUAL;
                interrupts();
            } else if (msg->getContent() == "MANUAL_OFF"){
                noInterrupts();
                currState = ALARM;
                interrupts();
            }
            Task::setPeriod(getPeriod());
        }
        delete msg;
    }
    float currWL = wlSensor->getDistance()*METERS_COV;

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
                blinktask->setActive(true);
                lcdMonitor->on();
                lcdMonitor->writePreAlarm("PRE-ALARM",currWL);
                MsgService.sendMsg("PRE-ALARM "+ (String) currWL);
            } else {
                blinktask->updateState();
            }
        }break;
        case ALARM:{
            int angle = map(currWL,WL_MAX,WL2,0,180);
            Serial.println(angle);
            if(switchAndCheckState(currWL)){
                greenLed->switchOff();
                redLed->switchOn();
                slTask->updateState();
                lcdMonitor->on();
                //valve->on();
                valve->setPosition(angle);
                lcdMonitor->writeAlarm("ALARM",currWL,angle);
                MsgService.sendMsg("ALARM "+ (String) currWL);
            } else {
                slTask->setActive(true);
                redLed->switchOff();
                //valve->off();
            }
        } break;
        case MANUAL: {
            int potAngle = pot->getAngle();
            if(last_pot != potAngle){
                pot_millis = millis();
                last_pot = potAngle;
            }
            greenLed->switchOff();
            redLed->switchOn();
            slTask->updateState();
            lcdMonitor->on();
            //valve->on();
            valve->setPosition(potAngle/*pot_millis >= msg_millis ? potAngle : msgAngle*/);
            lcdMonitor->writeAlarm("ALARM - MANUAL ON",currWL,potAngle/*pot_millis >= msg_millis ? potAngle : msgAngle*/);
            MsgService.sendMsg("MANUAL_ALARM "+ (String) currWL);
        }break;
    }
}

int WaterLevelTask::getPeriod(){
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
    Task::setPeriod(getPeriod());
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
        Task::setPeriod(getPeriod());
    }
    last_interrupt_time = interrupt_time;
}
