#include <Arduino.h>
#include <Logger.h>
#include <StepMotor.h>
#include <UTFT.h>
#include <Bluetooth.h>
#include <Radio.h>

// PORTS
#define INFRA_RED_OUT 8 // D8
#define BLUE_LED 9 // D9
#define RELAY_GAS 10 // D10
#define step_IN1 62 // A8
#define step_IN2 63 // A9
#define step_IN3 64 // A10
#define step_IN4 65 // A11

extern uint8_t SmallFont[];

// VARS
UTFT display(R61581,38,39,40,41);
StepMotor steper(step_IN1, step_IN2, step_IN3, step_IN4);
Bluetooth bluetooth;
Radio radio;
Logger Log;
int data;
int sendRequestFlag = 0;

void printTFT(String text, word color, int x, int y)
{
  display.drawLine(10, 10, 310, 10);
  display.drawLine(10, 230, 310, 230);
  display.setColor(color);
  display.print("                     ", x, y, 0);
  display.print(text, x, y, 0);
  display.setColor(VGA_WHITE);
}

void setup() 
{
  pinMode(INFRA_RED_OUT, OUTPUT); // set pin 8 as output
  pinMode(BLUE_LED, OUTPUT); // set pin 9 as output 
  pinMode(RELAY_GAS, INPUT); // set pin 10 as input

  display.InitLCD();
  display.setFont(SmallFont);
  display.clrScr();
}

void loop() 
{ 
  steper.Update();

  int relayGasData = digitalRead(RELAY_GAS);

  if (relayGasData == 0)
  {
    digitalWrite(BLUE_LED, 1); 
    digitalWrite(INFRA_RED_OUT, 1);

    radio.SendOk();
    bluetooth.SendOk();
    steper.StartClosing();
  }
  else 
  {
    digitalWrite(BLUE_LED, 0);
    digitalWrite(INFRA_RED_OUT, 0);

    radio.SendWarning();
    bluetooth.SendWarning();
    steper.StartOpening();
  }
}
