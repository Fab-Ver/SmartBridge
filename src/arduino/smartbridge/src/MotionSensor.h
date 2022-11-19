#ifndef __MOTION__SENSOR__
#define __MOTION__SENSOR__

class MotionSensor{
    public:
        virtual void updateStatus() = 0;
        virtual bool getStatus() = 0;
};

#endif