#include <Arduino.h>

class StepMotor
{
    private:
        byte _in1;
        byte _in2;
        byte _in3;
        byte _in4;

        bool _isTurningRight;
        bool _isTurningLeft;

        int _counterSteps;
        int _maxSteps;

    public:
        StepMotor(byte in1, byte in2, byte in3, byte in4, int maxSteps = 1024)
        {
            // Constructor //

            _in1 = in1;
            _in2 = in2;
            _in3 = in3;
            _in4 = in4;
            _maxSteps = maxSteps;
            _isTurningRight = false;
            _isTurningLeft = false;
            _counterSteps = 0;
        }

        void Update()
        {
            // Call this method every tick // 
            // Make single turn acording to flags //
            if (_isTurningRight)
            {
                if (_counterSteps < _maxSteps)
                {
                    TurnRight();
                    _counterSteps++;
                }
                else
                {
                    TurnOff();
                    _isTurningRight = false;
                }
            }
            else if (_isTurningLeft)
            {
                if (_counterSteps > 0)
                {
                    TurnLeft();
                    _counterSteps--;
                }
                else
                {
                    TurnOff();
                    _isTurningLeft = false;
                }
            }
        }

        void StartOpening()
        {
            // set flags to open //
            _isTurningRight = true;
            _isTurningLeft = false;
        }

        void StartClosing()
        {
            // set flags to close //
            _isTurningRight = false;
            _isTurningLeft = true;
        }

    private:
        void TurnRight()
        {
            // Turn motor right (clockwise) //
            SetAllPins(0,0,0,1);
            delay(1);
            SetAllPins(0,0,1,1);
            delay(1);
            SetAllPins(0,0,1,0);
            delay(1);
            SetAllPins(0,1,1,0);
            delay(1);
            SetAllPins(0,1,0,0);
            delay(1);
            SetAllPins(1,1,0,0);
            delay(1);
            SetAllPins(1,0,0,0);
            delay(1);
            SetAllPins(1,0,0,1);
            delay(1);
        }

        void TurnLeft()
        {
            // Turn motor left (no clockwise) //
            SetAllPins(1,0,0,1);
            delay(1);
            SetAllPins(1,0,0,0);
            delay(1);
            SetAllPins(1,1,0,0);
            delay(1);
            SetAllPins(0,1,0,0);
            delay(1);
            SetAllPins(0,1,1,0);
            delay(1);
            SetAllPins(0,0,1,0);
            delay(1);
            SetAllPins(0,0,1,1);
            delay(1);
            SetAllPins(0,0,0,1);
            delay(1);
        }

        void TurnOff()
        {
            // Turn off driver //
            SetAllPins(0,0,0,0);
        }

        void SetAllPins(byte in1, byte in2, byte in3, byte in4)
        {
            // Set all pins from in1 to in4 // 
            digitalWrite(_in1, in1);
            digitalWrite(_in2, in2);
            digitalWrite(_in3, in3);
            digitalWrite(_in4, in4);
        }
};