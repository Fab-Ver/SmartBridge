#ifndef __POTENTIOMETER__IMPL__
#define __POTENTIOMETER__IMPL__

#include "Potentiometer.h"

class PotentiometerImpl : public Potentiometer{   
    private:
        int pin;
    public:
        PotentiometerImpl(int pin);
        int getAngle();
};

#endif