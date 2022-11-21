#ifndef __WATER_LEVEL_TASK__
#define __WATER_LEVEL_TASK__

#include "Task.h"
#include "BlinkTask.h"
#include "SmartLightTask.h"
#include "Led.h"
#include "WaterLevelSensor.h"
#include "Valve.h"
#include "PotentiometerImpl.h"
#include "LcdImpl.h"

typedef enum WLState {NORMAL, PRE_ALARM, ALARM, MANUAL} WLState;

class WaterLevelTask : public Task {
    private:
        int trigPin, echoPin, valvePin, potPin, greenPin, redPin, buttonPin;
        Light* greenLed;
        Light* redLed;
        Sonar* wlSensor;
        ServoMotor* valve;
        Potentiometer* pot;
        Lcd* lcdMonitor;
        SmartLightTask* slTask;
        BlinkTask* blinktask;
        WLState currState;
        int getPeriod();
    public:
        WaterLevelTask(int trigPin, int echoPin, int valvePin, int potPin, int greenPin, int redPin, int buttonPin, SmartLightTask* slt, BlinkTask* bt);
        void init(int normalPeriod, int preAlarmPeriod, int alarmPeriod);
        void tick();
};


#endif