#include <ili9488_touch.h>
#include <ili9488.h>

#define LED 13

bool switch_state = false;

void OffState()
{
  lcd.Set_Draw_color(WHITE);
  lcd.Fill_Rectangle(109, 214, 159,264);
  lcd.Set_Text_colour(RED);
  lcd.Print("OFF", 119, 234);
                                  
  lcd.Set_Draw_color(BLACK);
  lcd.Fill_Rectangle(160, 214, 209, 264);

  digitalWrite(LED, LOW);
}

void OnState()
{
  lcd.Set_Draw_color(BLACK);
  lcd.Fill_Rectangle(109, 214, 159,264);
                                  
  lcd.Set_Draw_color(WHITE);
  lcd.Fill_Rectangle(160, 214, 209, 264);
  lcd.Set_Text_colour(GREEN);
  lcd.Print("ON", 174, 234);

  digitalWrite(LED, HIGH);
}

void setup() 
{
  pinMode(LED, OUTPUT);
  
  lcd.Init_LCD();
  lcd.Set_Rotation(2);
  
  lcd.Set_Text_Back_colour(WHITE);
  lcd.Fill_Screen(YELLOW); 
  lcd.Set_Text_Size(2);
  
  lcdT.TP_Init();

  OffState();
}

void loop() 
{
  if (lcdT.TP_Scan()) 
  {
    int x = lcdT.getX();
    int y = lcdT.getY();

    if(switch_state) {
      if((x >= 109 && x <= 159)  && (y >= 214 && y <= 264)) {
        switch_state = false;
        OffState();
      }
    }
    else {
      if((x >= 160 && x <= 209)  && (y >= 214 && y <= 264)) {
        switch_state = true;
        OnState();
      }
    }
  }
}
