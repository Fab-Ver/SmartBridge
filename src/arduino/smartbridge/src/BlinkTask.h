#ifndef __BLINK_TASK__
#define __BLINK_TASK__

#include "Task.h"
#include "Led.h"

class BlinkTask: public Task {
    private:
        int pin;
        Light* led;
        State currState;
    public:
        BlinkTask(int pin);  
        void init(int period);  
        void tick();
        void updateState();
};


#endif
