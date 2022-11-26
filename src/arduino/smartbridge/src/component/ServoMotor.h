#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

class ServoMotor {
    public:
        /*
            Reset the position of the servo motor.
        */
        virtual void close() = 0;

        /*
            Set the servo position to the specified angle.
        */
        virtual void setPosition(int angle) = 0;
};

#endif