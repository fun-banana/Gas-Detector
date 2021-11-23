#include <Arduino.h>
#include <ili9488.h>

void setup() 
{
  lcd.Init_LCD();
  lcd.Fill_Screen(BLACK);

  Serial.begin(9600);
  Serial.print("test");
}

void loop() 
{
  lcd.Set_Text_Mode(0);
  //display 1 times string
  lcd.Fill_Screen(0x0000);
  lcd.Set_Text_colour(RED);
  lcd.Set_Text_Back_colour(BLACK); 
}