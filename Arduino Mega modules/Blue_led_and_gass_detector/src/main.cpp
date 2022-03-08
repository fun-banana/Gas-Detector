#include <Arduino.h>
#include <Stepper.h>
#include <SoftwareSerial.h>

// PORTS
const int INFRA_RED_OUT = 8; 
const int BLUE_LED = 9;
const int RELAY_GAS = 10;
const int step_IN1 = 62; // A8
const int step_IN2 = 63; // A9
const int step_IN3 = 64; // A10
const int step_IN4 = 65; // A11
const int radio_rx = 10; // D16
const int radio_tx = 11; // D17

// CONSTANTS
const int stepPerRevolution = 200;
const int stepSpeed = 60;

// VARS
Stepper stepMotor(stepPerRevolution, step_IN1, step_IN2, step_IN3, step_IN4);
String ack = "";
SoftwareSerial radio(radio_rx, radio_tx);

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
  Serial.println("Turn right\n");
}

void turn_left(Stepper motor)
{
  motor.step(-stepPerRevolution);
  Serial.println("Turn left\n");
}

void setup() 
{
  pinMode(INFRA_RED_OUT, OUTPUT); // set pin 8 as output
  pinMode(BLUE_LED, OUTPUT); // set pin 9 as output 
  pinMode(RELAY_GAS, INPUT); // set pin 10 as input

  stepMotor.setSpeed(stepSpeed);
  turn_left(stepMotor);

  Serial.begin(9600); // open serial port
  radio.begin(2400); // open radio port
}

void loop() 
{ 
  int relayGasData = digitalRead(RELAY_GAS);

  // while (radio.available())
  // {
  //   ack = radio.readString();
  //   Serial.println(ack);
  // }

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
    Serial.write("ok");

    radio.println("Hello, World!");
  }

  // Serial.println(relayGasData);
}

void yield()
{
  if (Serial.available())
  {
    byte a = Serial.read();
    Serial.println(a);
  }
}