#include <Arduino.h>

class Logger
{
    public:
        #define DEBUG   "DEBUG"
        #define INFO    "INFO"
        #define WARNING "WARNING"
        #define ERROR   "ERROR"

    void Log(String text, String logLevel = DEBUG)
    {
        if (!isLogLevel(logLevel))
            return;

        Serial.println("=============================");
        Serial.println("["+logLevel+"]:\t"+text+"\n");
    }

    private:
        bool isLogLevel(String logLevel)
        {
            return  logLevel == DEBUG  ||
                    logLevel == INFO   ||
                    logLevel == WARNING||
                    logLevel == ERROR;
        }
};