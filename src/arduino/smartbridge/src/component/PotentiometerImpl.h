#ifndef __POTENTIOMETER__IMPL__
#define __POTENTIOMETER__IMPL__

#include "Potentiometer.h"

class PotentiometerImpl : public Potentiometer{   
    public:
        PotentiometerImpl(int pin);
        int getAngle();
    private:
        int pin;
};

#endif