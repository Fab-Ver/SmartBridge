#ifndef __SMARTLIGHT_TASK__
#define __SMARTLIGHT_TASK__

#include "Task.h"
#include "Led.h"
#include "LightSensorImpl.h"
#include "MotionSensorImpl.h"

class SmartLightTask : public Task{
    private:
        int ledPin, msPin, lsPin;
        Light* led;
        LighSensor* ls;
        MotionSensor* ms;
        State currState;
    public:
        SmartLightTask(int ledPin, int lsPin, int msPin);
        void init(int period);
        void tick();
        void updateState();
};
#endif