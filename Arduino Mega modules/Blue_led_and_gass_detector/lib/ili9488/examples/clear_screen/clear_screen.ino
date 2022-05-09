#include "ili9488.h"

void setup() 
{
    lcd.Init_LCD(); //initialize lcd
    lcd.Fill_Screen(WHITE); //display white
}

void loop() 
{ 
    //Sequential display black,white,red,green,blue
    lcd.Fill_Screen(0,0,0);  
    lcd.Fill_Screen(255,255,255); 
    lcd.Fill_Screen(255,0,0); 
    lcd.Fill_Screen(0,255,0);
    lcd.Fill_Screen(0,0,255);
    delay(3000);
    lcd.Fill_Screen(BLACK);
    delay(1000);
    lcd.Fill_Screen(WHITE);
    delay(1000);
    lcd.Fill_Screen(RED);
    delay(1000);
    lcd.Fill_Screen(GREEN);
    delay(1000);
    lcd.Fill_Screen(BLUE);
    delay(1000);
}
