#ifndef __BLINK_TASK__
#define __BLINK_TASK__

#include "Task.h"
#include "Led.h"
#include "config.h"

typedef enum StateB {ON, OFF, BLINK_OFF} StateB;

class BlinkTask: public Task {
    private:
        int pin;
        Light* led;
        StateB currState;
    public:
        BlinkTask(int pin);  
        void init(int period);  
        void tick();
        void updateState();
};

#endif
