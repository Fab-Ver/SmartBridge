#ifndef __LCD__
#define __LCD__

#include <Arduino.h>

class Lcd {
    public:
        /*
            Switch on the lcd monitor. 
        */
        virtual void on() = 0;

        /*
            Switch off the lcd monitor.
        */
        virtual void off() = 0;

        /*
            Write messages on the lcd monitor during pre-alarm status. 
        */
        virtual void writePreAlarm(String msg, float waterLevel) = 0;

        /*
            Write messages on the lcd monitor during alarm status. 
        */
        virtual void writeAlarm(String msg, float waterLevel, int angle) = 0;
};

#endif