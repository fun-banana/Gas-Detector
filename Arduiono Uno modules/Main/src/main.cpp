#include <Arduino.h>
#include <SoftwareSerial.h>

// ports
int radio_rx = 0;
int radio_tx = 1;

// vars
SoftwareSerial radio(radio_rx, radio_tx);

void setup() 
{
  radio.begin(2400);
  Serial.begin(9600);
}

void loop() 
{
  if (radio.available())
  {
    Serial.println(radio.readString());
  }
}