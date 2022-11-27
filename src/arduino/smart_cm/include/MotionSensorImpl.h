#ifndef __MOTION_SENSOR_IMPL__
#define __MOTION_SENSOR_IMPL__

#include "MotionSensor.h"

class MotionSensorImpl : public MotionSensor{
    private:
        int pin;
    public:
        MotionSensorImpl(int pin);
        bool isDetected();
};

#endif