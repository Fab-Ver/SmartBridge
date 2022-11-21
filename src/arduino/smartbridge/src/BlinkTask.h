#ifndef __BLINK_TASK__
#define __BLINK_TASK__

#include "Task.h"
#include "Led.h"

typedef enum BTState { LIGHT_ON, LIGHT_OFF, BLINK_OFF} BTState;

class BlinkTask: public Task {
    private:
        int pin;
        Light* led;
        BTState currState;
    public:
        BlinkTask(int pin);  
        void init(int period);  
        void tick();
        void setState(BTState state);
};


#endif
