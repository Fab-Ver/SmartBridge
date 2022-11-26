#ifndef __VALVE__
#define __VALVE__

#include <Arduino.h>
#include "ServoTimer2.h"
#include "ServoMotor.h"

class Valve : public ServoMotor{
    private:
        ServoTimer2 motor;
    public:
        Valve(int pin);
        void close();
        void setPosition(int angle);
};

#endif