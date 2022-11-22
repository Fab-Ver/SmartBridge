#ifndef __LCD__
#define __LCD__

#include <Arduino.h>

class Lcd {
    public:
        virtual void on() = 0;
        virtual void off() = 0;
        virtual void writePreAlarm(String msg, int waterLevel) = 0;
        virtual void writeAlarm(String msg, int waterLevel, int angle) = 0;
};
#endif