#include <Arduino.h>
#include <Stepper.h>

// PORTS
const int INFRA_RED_OUT = 8; 
const int BLUE_LED = 9;
const int RELAY_GAS = 10;
const int step_IN1 = 62; // A8
const int step_IN2 = 63; // A9
const int step_IN3 = 64; // A10
const int step_IN4 = 65; // A11

// CONSTANTS
const int stepPerRevolution = 200;
const int stepSpeed = 60;

// VARS
Stepper stepMotor(stepPerRevolution, step_IN1, step_IN2, step_IN3, step_IN4);

void turn_right(Stepper motor)
{
  motor.step(stepPerRevolution);
}

void turn_left(Stepper motor)
{
  motor.step(-stepPerRevolution);
}

void setup() 
{
  pinMode(INFRA_RED_OUT, OUTPUT); // set pin 8 as output
  pinMode(BLUE_LED, OUTPUT); // set pin 9 as output 
  pinMode(RELAY_GAS, INPUT); // set pin 10 as input

  stepMotor.setSpeed(stepSpeed);

  Serial.begin(9600); // open serial port
}

void loop() 
{ 
  int relayGasData = digitalRead(RELAY_GAS);

  if (relayGasData == 0)
  {
    digitalWrite(BLUE_LED, 1); 
    digitalWrite(INFRA_RED_OUT, 1);
    turn_left(stepMotor);
  }
  else 
  {
    digitalWrite(BLUE_LED, 0);
  }

  Serial.println(relayGasData);
}