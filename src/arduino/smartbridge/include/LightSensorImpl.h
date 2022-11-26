#ifndef __LIGHTSENSOR_IMPL__
#define __LIGHTSENSOR_IMPL__

#include "LightSensor.h"

class LightSensorImpl : public LightSensor {
    private:
        int pin;
    public:
        LightSensorImpl(int pin);
        bool isDark();
};

#endif