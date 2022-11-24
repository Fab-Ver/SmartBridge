#ifndef __LIGHTSENSOR__
#define __LIGHTSENSOR__

class LightSensor {
    public:
        /*
            Report the environment light level, true if light level 
            is smaller then a certain threshold. 
        */
        virtual bool isDark() = 0;
};

#endif