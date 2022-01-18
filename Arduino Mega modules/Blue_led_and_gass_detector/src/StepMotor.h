#include <Arduino.h>

class StepMotor
{
    public:
        StepMotor(byte IN1, byte IN2, byte IN3, byte IN4)
        {
            _IN1 = IN1;
            _IN2 = IN2;
            _IN3 = IN3;
            _IN4 = IN4;
        }

    private:
        byte _IN1;
        byte _IN2;
        byte _IN3;
        byte _IN4;
};