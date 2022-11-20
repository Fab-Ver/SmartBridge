#ifndef __VALVE__
#define __VALVE__

#include "ServoTimer2.h"
#include "ServoMotor.h"

class Valve : public ServoMotor{
    private:
        int pin;
        ServoTimer2 motor;
    public:
        Valve(int pin);
        void on();
        void off();
        void setPosition(int angle);
};
#endif