#include <Arduino.h>
#include <HardwareSerial.h>

class Bluetooth
{
    private:
        bool _isAlreadySendWarning;
        bool _isAlreadySendOk;

    public:
        Bluetooth(HardwareSerial serial)
        {
            Serial3.begin(9600);
            _isAlreadySendWarning = false;
            _isAlreadySendOk = false;
        }

        void SendWarning()
        {
            if (!_isAlreadySendWarning)
            {
                Serial3.write("Warning\n");
                _isAlreadySendWarning = true;
                _isAlreadySendOk = false;
            }
        }

        void SendOk()
        {
            if (!_isAlreadySendOk)
            {
                Serial3.write("Ok\n");
                _isAlreadySendOk = true;
                _isAlreadySendWarning = false;
            }
        }
};