#include <Arduino.h>
#include <Logger.h>
#include <StepMotor.h>
#include <Bluetooth.h>
#include <Radio.h>
#include <Lcd.h>

// PORTS
#define INFRA_RED_OUT 8 // D8
#define BLUE_LED 9 // D9
#define RELAY_GAS 10 // D10
#define step_IN1 62 // A8
#define step_IN2 63 // A9
#define step_IN3 64 // A10
#define step_IN4 65 // A11

// VARS
StepMotor steper(step_IN1, step_IN2, step_IN3, step_IN4);
Bluetooth bluetooth;
Radio radio;
Logger Log;
Lcd display;
int data;
int sendRequestFlag = 0;

// Setup
void setup() 
{
  pinMode(INFRA_RED_OUT, OUTPUT); // set pin 8 as output
  pinMode(BLUE_LED, OUTPUT); // set pin 9 as output 
  pinMode(RELAY_GAS, INPUT); // set pin 10 as input

  display.Setup();
  display.PrintDisplayStartInfo();
  delay(3000);
  display.Clear();
}

// Loop
void loop() 
{ 
  steper.Update();

  int relayGasData = digitalRead(RELAY_GAS);

  if (relayGasData == 0)
  {
    digitalWrite(BLUE_LED, 1); 
    digitalWrite(INFRA_RED_OUT, 1);

    display.PrintOkayStatus();
    radio.SendOk();
    bluetooth.SendOk();
    steper.StartClosing();
  }
  else 
  {
    digitalWrite(BLUE_LED, 0);
    digitalWrite(INFRA_RED_OUT, 0);

    display.PrintWarningStatus();
    radio.SendWarning();
    bluetooth.SendWarning();
    steper.StartOpening();
  }
}
