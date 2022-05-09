#include <Arduino.h>

class Radio
{
    private:
        bool _isAlreadySendWarning;
        bool _isAlreadySendOk;

    public:
        Radio(HardwareSerial serial)
        {
            Serial2.begin(9600);
            _isAlreadySendWarning = false;
            _isAlreadySendOk = false;
        }

        void SendWarning()
        {
            if (!_isAlreadySendWarning)
            {
                Serial2.write("Warning\n");
                _isAlreadySendWarning = true;
                _isAlreadySendOk = false;
            }
        }

        void SendOk()
        {
            if (!_isAlreadySendOk)
            {
                Serial2.write("Ok\n");
                _isAlreadySendOk = true;
                _isAlreadySendWarning = false;
            }
        }
};