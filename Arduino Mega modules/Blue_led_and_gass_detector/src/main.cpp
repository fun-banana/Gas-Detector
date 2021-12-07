#include <Arduino.h>

// VARIABLES
int BLUE_LED = 9;
int RELAY_GAS = 10; 

void setup() 
{
  pinMode(BLUE_LED, OUTPUT); // set pin 9 as output 
  pinMode(RELAY_GAS, INPUT); // set pin 10 as input
  Serial.begin(9600); // open serial port
}

void loop() 
{
  Serial.println(digitalRead(RELAY_GAS)); // write to serial port Relay gas status (0 \ 1)

  digitalWrite(BLUE_LED, digitalRead(RELAY_GAS)); // turn on LED when Relay gas (pin 10) get 1 logic
}