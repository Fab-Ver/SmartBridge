#ifndef __SMARTLIGHT_TASK__
#define __SMARTLIGHT_TASK__

#include "Task.h"
#include "Led.h"
#include "LightSensorImpl.h"
#include "MotionSensorImpl.h"

typedef enum SLState {ON, OFF} SLSate;

class SmartLightTask : public Task{
    private:
        int ledPin, msPin, lsPin;
        Light* led;
        LighSensor* ls;
        MotionSensor* ms;
        SLState currState;
    public:
        SmartLightTask(int ledPin, int lsPin, int msPin);
        void init(int period);
        void tick();
};
#endif