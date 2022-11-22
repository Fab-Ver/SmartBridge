#ifndef __LIGHTSENSOR_IMPL__
#define __LIGHTSENSOR_IMPL__

#include "LightSensor.h"

class LighSensorImpl : public LighSensor {
    public:
        LighSensorImpl(int pin);
        int getIntensity();
    private:
        int pin;
};

#endif