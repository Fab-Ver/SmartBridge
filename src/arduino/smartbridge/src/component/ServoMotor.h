#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

class ServoMotor {
    public:
        /*
            Attaches a servo motor to pin.
        */
        virtual void on() = 0;

        /*
            Detach a servo motor to pin.
        */
        virtual void off() = 0;

        /*
            Set the servo position to the specified angle.
        */
        virtual void setPosition(int angle) = 0;
};

#endif