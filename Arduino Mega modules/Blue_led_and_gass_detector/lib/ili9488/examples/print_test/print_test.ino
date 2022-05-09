#include "ili9488.h"

void setup() 
{
  lcd.Init_LCD();
  lcd.Fill_Screen(BLACK);
}

void loop() 
{
  lcd.Set_Text_Mode(0);
  //display 1 times string
  lcd.Fill_Screen(0x0000);
  lcd.Set_Text_colour(RED);
  lcd.Set_Text_Back_colour(BLACK);
  lcd.Set_Text_Size(1);
  lcd.Print_String("Hello World!", 0, 0);
  lcd.Print_Number_Float(01234.56789, 2, 0, 8, '.', 0, ' ');  
  lcd.Print_Number_Int(0xDEADBEF, 0, 16, 0, ' ',16);
  //lcd.Print_String("DEADBEF", 0, 16);

  //display 2 times string
  lcd.Set_Text_colour(GREEN);
  lcd.Set_Text_Size(2);
  lcd.Print_String("Hello World!", 0, 40);
  lcd.Print_Number_Float(01234.56789, 2, 0, 56, '.', 0, ' ');  
  lcd.Print_Number_Int(0xDEADBEF, 0, 72, 0, ' ',16);
  //lcd.Print_String("DEADBEEF", 0, 72);

  //display 3 times string
  lcd.Set_Text_colour(BLUE);
  lcd.Set_Text_Size(3);
  lcd.Print_String("Hello World!", 0, 104);
  lcd.Print_Number_Float(01234.56789, 2, 0, 128, '.', 0, ' ');  
  lcd.Print_Number_Int(0xDEADBEF, 0, 152, 0, ' ',16);
 // lcd.Print_String("DEADBEEF", 0, 152);

  //display 4 times string
  lcd.Set_Text_colour(WHITE);
  lcd.Set_Text_Size(4);
  lcd.Print_String("Hello!", 0, 192);

  //display 5 times string
  lcd.Set_Text_colour(YELLOW);
  lcd.Set_Text_Size(5);
  lcd.Print_String("Hello!", 0, 224);

  //display 6 times string
  lcd.Set_Text_colour(RED);
  lcd.Set_Text_Size(6);
  lcd.Print_String("Hello!", 0, 266);

  delay(3000);
}
