#include <Arduino.h>

// VARIABLES
int INFRA_RED_OUT = 8; 
int BLUE_LED      = 9;
int RELAY_GAS     = 10;

void setup() 
{
  pinMode(INFRA_RED_OUT, OUTPUT); // set pin 8 as output
  pinMode(BLUE_LED, OUTPUT); // set pin 9 as output 
  pinMode(RELAY_GAS, INPUT); // set pin 10 as input
  Serial.begin(9600); // open serial port
}

void loop() 
{ 
  int relayGasData = digitalRead(RELAY_GAS);

  if (relayGasData == 0)
  {
    digitalWrite(BLUE_LED, 1); 
    digitalWrite(INFRA_RED_OUT, 1);
  }
  else 
  {
    digitalWrite(BLUE_LED, 0);
  }

  Serial.println(relayGasData);
}