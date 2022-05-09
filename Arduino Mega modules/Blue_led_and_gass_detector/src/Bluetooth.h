#include <Arduino.h>
#include <HardwareSerial.h>

class Bluetooth
{
    private:
        bool _isAlreadySendWarning; // Check is Warining message was already send
        bool _isAlreadySendOk; // Check is Ok message was already send

    public:
        Bluetooth()
        {
            Serial3.begin(9600); // Open Srial port number 3  (that is rx3 and tx3)
            _isAlreadySendWarning = false; // Reset to false a variable
            _isAlreadySendOk = false; // Reset to false a variable
        }

        void SendWarning()
        {
            if (!_isAlreadySendWarning) // Check is message was already send
            {
                Serial3.write("Warning\n"); // Write to Serial port message
                _isAlreadySendWarning = true; // Set flag to True a variable
                _isAlreadySendOk = false; // Reset to false a variable
            }
        }

        void SendOk()
        {
            if (!_isAlreadySendOk) // Check is message was already send
            {
                Serial3.write("Ok\n"); // Write to Serial port message
                _isAlreadySendOk = true; // Set flag to True a variable
                _isAlreadySendWarning = false; // Reset to false a variable
            }
        }
};