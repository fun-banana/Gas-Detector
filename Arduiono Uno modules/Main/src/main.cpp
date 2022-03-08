#include <Arduino.h>
#include <SoftwareSerial.h>
#include <UTFT.h>

// ports
const int radio_rx = 1;
const int radio_tx = 1;
const int red_led = 16; 
const int green_led = 15;
const int blue_led = 14;

// vars
SoftwareSerial radio(radio_rx, radio_tx);
UTFT myGLCD(ILI9341_S5P,11,13,10,8,9);
extern uint8_t BigFont[];

uint32_t myTimer1;

int curent_state = 0;
bool is_draw_alerm = false;
bool is_draw_ok = false;

void printTFT(String text, word color, int x, int y)
{
  // myGLCD.clrScr();
  myGLCD.drawLine(10, 10, 310, 10);
  myGLCD.drawLine(10, 230, 310, 230);
  myGLCD.setColor(color);
  myGLCD.print("                     ", x, y, 0);
  myGLCD.print(text, x, y, 0);
  myGLCD.setColor(VGA_WHITE);
}

void setup() 
{
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);

  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);
  printTFT("Status: HELLO", VGA_YELLOW, CENTER, 50);

  radio.begin(2400);
  Serial.begin(9600);
}

void loop() 
{
  if (1 == 1)
  {
    Serial.println("HELLO");
    if (!is_draw_alerm)
    {
      printTFT("Gas: off", VGA_YELLOW, CENTER, 50);
      is_draw_alerm = true;
    }
    printTFT("ALARM", VGA_RED, CENTER, 100);
    digitalWrite(blue_led, 0);

    if (millis() - myTimer1 >= 25) {   
      myTimer1 = millis();

      digitalWrite(green_led, curent_state);
      
      if (curent_state == 0)
      {
        digitalWrite(red_led, 1);
      }
      else
      {
        digitalWrite(red_led, 0);
      }


      if (curent_state == 0) {curent_state = 1;}
      else {curent_state = 0;}
    }

    is_draw_ok = false;
  }
  else 
  {
    if (!is_draw_ok)
    {
      printTFT("Gas: on", VGA_LIME, CENTER, 50);
      printTFT("Status: OK", VGA_LIME, CENTER, 100);
      is_draw_ok = true;
    }
    digitalWrite(blue_led, 1);
    digitalWrite(green_led, 1);
    digitalWrite(red_led, 0);

        is_draw_alerm = false;
  }
}