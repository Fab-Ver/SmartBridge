#ifndef __MOTION_SENSOR_IMPL__
#define __MOTION_SENSOR_IMPL__

#include "MotionSensor.h"

class MotionSensorImpl : public MotionSensor{
    public:
        MotionSensorImpl(int pin);
        void updateStatus();
        bool getStatus();
    private:
        bool detectedStatus;
        int pin;
};

#endif