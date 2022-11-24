#ifndef __MOTION__SENSOR__
#define __MOTION__SENSOR__

class MotionSensor{
    public:
        /*
            Return true if an object is detected, false otherwise. 
        */
        virtual bool isDetected() = 0;
};

#endif