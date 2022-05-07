#include <Arduino.h>
#include <Logger.h>
#include <StepMotor.h>

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
Logger Log;
int data;
int sendRequestFlag = 0;

void setup() 
{
  pinMode(INFRA_RED_OUT, OUTPUT); // set pin 8 as output
  pinMode(BLUE_LED, OUTPUT); // set pin 9 as output 
  pinMode(RELAY_GAS, INPUT); // set pin 10 as input

  Serial.begin(9600); // open serial port
  Serial2.begin(9600); // open serial radio port
  Serial3.begin(9600); // open serial bluetooth port
}

void loop() 
{ 
  steper.Update();

  int relayGasData = digitalRead(RELAY_GAS);

  if (relayGasData == 0)
  {
    digitalWrite(BLUE_LED, 1); 
    digitalWrite(INFRA_RED_OUT, 1);

    sendRequestFlag = 1;
    steper.StartClosing();
  }
  else 
  {
    digitalWrite(BLUE_LED, 0);
    digitalWrite(INFRA_RED_OUT, 0);

    Serial3.write("WARNING\n");

    if (sendRequestFlag == 1)
    {
      sendRequestFlag = 0;
      Serial2.println('1');
    }

    steper.StartOpening();
  }
}
