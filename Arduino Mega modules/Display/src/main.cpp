#include <Arduino.h>
#include <TFT.h>

#define cs   10
#define dc   9
#define rst  8

TFT TFTscreen = TFT(cs, dc, rst);

void setup() 
{
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  TFTscreen.stroke(255,255,255);
  TFTscreen.setTextSize(2);
  TFTscreen.text("Test", 0, 0);
  TFTscreen.setTextSize(5);

  Serial.begin(9600);
  Serial.print("test");
}

void loop() 
{
  
}