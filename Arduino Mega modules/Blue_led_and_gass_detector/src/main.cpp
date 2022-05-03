#include <Arduino.h>
#include <Stepper.h>
#include <SoftwareSerial.h>
#include <Logger.h>

// PORTS
#define INFRA_RED_OUT 8 // D8
#define BLUE_LED 9 // D9
#define RELAY_GAS 10 // D10
#define step_IN1 62 // A8
#define step_IN2 63 // A9
#define step_IN3 64 // A10
#define step_IN4 65 // A11

// CONSTANTS
const int stepPerRevolution = 200;
const int stepSpeed = 60;

// VARS
Stepper stepMotor(stepPerRevolution, step_IN1, step_IN2, step_IN3, step_IN4);
Logger Log;
int data;

void turn_off(Stepper motor)
{
  digitalWrite(step_IN1, 0);
  digitalWrite(step_IN2, 0);
  digitalWrite(step_IN3, 0);
  digitalWrite(step_IN4, 0);
}

void turn_right(Stepper motor)
{
  motor.step(stepPerRevolution);
  Log.Log("Turn right", INFO);
}

void turn_left(Stepper motor)
{
  motor.step(-stepPerRevolution);
  Log.Log("Turn left", INFO);
}

void setup() 
{
  pinMode(INFRA_RED_OUT, OUTPUT); // set pin 8 as output
  pinMode(BLUE_LED, OUTPUT); // set pin 9 as output 
  pinMode(RELAY_GAS, INPUT); // set pin 10 as input

  stepMotor.setSpeed(stepSpeed);
  turn_left(stepMotor);

  Serial.begin(9600); // open serial port
  Serial2.begin(9600); // open serial radio port
  Serial3.begin(9600); // open serial bluetooth port
}

void loop() 
{ 
  int relayGasData = digitalRead(RELAY_GAS);

  while (Serial3.available() > 0)
  {
    Log.Log(Serial3.readString());
  }

  if (data != 0)
  {
    Serial.println(data);
  }

  if (relayGasData == 0)
  {
    digitalWrite(BLUE_LED, 1); 
    digitalWrite(INFRA_RED_OUT, 1);

    turn_off(stepMotor);
  }
  else 
  {
    digitalWrite(BLUE_LED, 0);
    digitalWrite(INFRA_RED_OUT, 0);

    turn_right(stepMotor);
  }

    Serial3.write("WARNING");
    Serial2.write("WARNING");
}
