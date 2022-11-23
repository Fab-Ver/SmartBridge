#ifndef __LCD__
#define __LCD__

#include <Arduino.h>

class Lcd {
    public:
        virtual void on() = 0;
        virtual void off() = 0;
        virtual void writePreAlarm(String msg, float waterLevel) = 0;
        virtual void writeAlarm(String msg, float waterLevel, int angle) = 0;
};

#endif