#include <Arduino.h>
#include <Stepper.h>

class StepMotor
{
    private:
        byte _IN1;
        byte _IN2;
        byte _IN3;
        byte _IN4;

        int _stepPerRevolution = 200;
        int _stepSpeed = 60;

        Stepper _stepMotor;

    public:
        // StepMotor(byte IN1, byte IN2, byte IN3, byte IN4)
        // {
        //     // Constructor //

        //     _IN1 = IN1;
        //     _IN2 = IN2;
        //     _IN3 = IN3;
        //     _IN4 = IN4;

        //     Stepper temp(_stepPerRevolution, _IN1, _IN2, _IN3, _IN4);

        //     _stepMotor = temp;
        //     _stepMotor.setSpeed(_stepSpeed);
        // }

        void TurnOff()
        {
            // Turn off driver //

            digitalWrite(_IN1, 0);
            digitalWrite(_IN2, 0);
            digitalWrite(_IN3, 0);
            digitalWrite(_IN4, 0);
        }

        void TurnRight()
        {
            // Turn motor right (clockwise) //

            _stepMotor.step(_stepPerRevolution);
            Serial.println("Turn right\n");
        }
};