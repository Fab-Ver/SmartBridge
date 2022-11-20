#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

class ServoMotor {
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void setPosition(int angle);
};

#endif