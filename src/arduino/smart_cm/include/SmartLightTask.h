#ifndef __SMARTLIGHT_TASK__
#define __SMARTLIGHT_TASK__

#include "Task.h"
#include "config.h"
#include "Led.h"
#include "LightSensorImpl.h"
#include "MotionSensorImpl.h"

typedef enum StateSM {LIGHT_ON, LIGHT_OFF, WAITING, SYS_OFF} StateSM;

class SmartLightTask : public Task{
    private:
        int ledPin, msPin, lsPin;
        Light* led;
        LightSensor* ls;
        MotionSensor* ms;
        StateSM currState;
    public:
        SmartLightTask(int ledPin, int lsPin, int msPin);
        void init(int period);
        void tick();
        void updateState();
};

#endif