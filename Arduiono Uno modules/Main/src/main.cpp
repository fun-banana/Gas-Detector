#include <Arduino.h>
#include <UTFT.h>

// ports
#define red_led 16
#define green_led 15
#define blue_led 14

// vars
UTFT myGLCD(ILI9341_S5P,11,13,10,8,9);
extern uint8_t BigFont[];
uint32_t myTimer1;
int curent_state = 0;
bool is_warning = false;
bool is_draw_alerm = false;
bool is_draw_ok = false;

// Print to display text 
void printTFT(String text, word color, int x, int y)
{
  myGLCD.drawLine(10, 10, 310, 10);
  myGLCD.drawLine(10, 230, 310, 230);
  myGLCD.setColor(color);
  myGLCD.print("                     ", x, y, 0);
  myGLCD.print(text, x, y, 0);
  myGLCD.setColor(VGA_WHITE);
}

// Setup 
void setup() 
{
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);

  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);
  printTFT("Gas Detector System", VGA_YELLOW, CENTER, 50);

  Serial.begin(9600);
  Serial.println("Starting poling");
}

void loop() 
{
  String data; // data from radio module

  if (Serial.available() > 0)
  {
    data = Serial.readString();
    Serial.println(data);
  }

  // Change flag acording to input data from radio
  if (data.compareTo("Warning\n") == 0)
  {
    is_warning = true;
  }
  else if (data.compareTo("Ok\n") == 0)
  {
    is_warning = false;
  }

  // if warning is true then:
  if (is_warning)
  {
    // Check is text was already draw in display
    if (!is_draw_alerm)
    {
      printTFT("Gas: off", VGA_YELLOW, CENTER, 50);
      is_draw_alerm = true;
    }
    printTFT("ALARM", VGA_RED, CENTER, 100);
    digitalWrite(blue_led, 0);

    // Make faux blink using Timer
    if (millis() - myTimer1 >= 25) 
    {   
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
  else // if warning is false then:
  {
    // Check is text was already draw in display
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