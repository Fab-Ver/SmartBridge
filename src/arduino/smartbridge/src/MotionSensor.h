#ifndef __MOTION__SENSOR__
#define __MOTION__SENSOR__

class MotionSensor{
    public:
        virtual bool updateStatus() = 0;
};

#endif