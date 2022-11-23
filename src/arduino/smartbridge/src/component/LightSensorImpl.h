#ifndef __LIGHTSENSOR_IMPL__
#define __LIGHTSENSOR_IMPL__

#include "LightSensor.h"

class LightSensorImpl : public LightSensor {
    public:
        LightSensorImpl(int pin);
        bool isDark();
    private:
        int pin;
};

#endif