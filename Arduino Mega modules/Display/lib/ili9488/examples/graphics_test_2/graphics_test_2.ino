#include "ili9488.h"

//clear screen
void fill_screen_test()
{
  lcd.Fill_Screen(BLACK);  
  lcd.Fill_Screen(RED);
  lcd.Fill_Screen(GREEN);
  lcd.Fill_Screen(BLUE);
  lcd.Fill_Screen(BLACK);
}

//display some strings
void text_test()
{
  lcd.Set_Text_Mode(0);
  
  lcd.Fill_Screen(BLACK);  
  lcd.Set_Text_Back_colour(BLACK);
  lcd.Set_Text_colour(WHITE);
  lcd.Set_Text_Size(1);
  lcd.Print_String("Hello World!", 0, 0);
  
  lcd.Set_Text_colour(YELLOW);
  lcd.Set_Text_Size(2);
  lcd.Print_Number_Float(1234.56,2,0, 8, '.', 0, ' ');
  
  lcd.Set_Text_colour(RED);
  lcd.Set_Text_Size(3);
  //lcd.Print_String("DEADBEEF", 0, 24); 
  lcd.Print_Number_Int(0xDEADBEF, 0, 24, 0, ' ', 16); 

  lcd.Set_Text_colour(GREEN);
  lcd.Set_Text_Size(5);  
  lcd.Print_String("Groop", 0, 56); 

  lcd.Set_Text_Size(2);
  lcd.Print_String("I implore thee,", 0, 96);

  lcd.Set_Text_Size(1);
  lcd.Print_String("my foonting turlingdromes.", 0, 112);
  lcd.Print_String("And hooptiously drangle me", 0, 120);
  lcd.Print_String("with crinkly bindlewurdles,", 0, 128);
  lcd.Print_String("Or I will rend thee", 0, 136);
  lcd.Print_String("in the gobberwarts", 0, 144);
  lcd.Print_String("with my blurglecruncheon,", 0, 152);
  lcd.Print_String("see if I don't!", 0, 160);
}

//draw some oblique lines
void lines_test(void)
{
    lcd.Fill_Screen(BLACK);
      lcd.Set_Draw_color(GREEN);
    int i = 0;   
    for(i = 0; i< lcd.Get_Display_Width();i+=5)
    {
       lcd.Draw_Line(0, 0, i, lcd.Get_Display_Height()-1);
     }
     for(i = lcd.Get_Display_Height()-1; i>= 0;i-=5)
     {
       lcd.Draw_Line(0, 0, lcd.Get_Display_Width()-1, i);
     }
     
     lcd.Fill_Screen(BLACK); 
       lcd.Set_Draw_color(RED);
    for(i = lcd.Get_Display_Width() -1; i>=0;i-=5)
    {
      lcd.Draw_Line(lcd.Get_Display_Width()-1, 0, i, lcd.Get_Display_Height()-1);
     }
    for(i = lcd.Get_Display_Height()-1; i>=0;i-=5)
    {
      lcd.Draw_Line(lcd.Get_Display_Width()-1, 0, 0, i);
     }
     
     lcd.Fill_Screen(BLACK); 
      lcd.Set_Draw_color(BLUE);
     for(i = 0; i < lcd.Get_Display_Width();i+=5)
    {
      lcd.Draw_Line(0, lcd.Get_Display_Height()-1, i, 0);
     }
     for(i = 0; i < lcd.Get_Display_Height();i+=5)
    {
      lcd.Draw_Line(0, lcd.Get_Display_Height()-1, lcd.Get_Display_Width()-1, i);
     }

     lcd.Fill_Screen(BLACK);
      lcd.Set_Draw_color(YELLOW);
     for(i = lcd.Get_Display_Width()-1; i >=0;i-=5)
    {
      lcd.Draw_Line(lcd.Get_Display_Width()-1, lcd.Get_Display_Height()-1, i, 0);
     }
     for(i = 0; i<lcd.Get_Display_Height();i+=5)
    {
      lcd.Draw_Line(lcd.Get_Display_Width()-1, lcd.Get_Display_Height()-1, 0, i);
     }
}

//draw some vertical lines and horizontal lines
void h_l_lines_test(void)
{
    int i=0;
   lcd.Fill_Screen(BLACK);
     lcd.Set_Draw_color(GREEN);
    for(i =0;i<lcd.Get_Display_Height();i+=5)
    {
      lcd.Draw_Fast_HLine(0,i,lcd.Get_Display_Width()); 
      delay(5);
    }
     lcd.Set_Draw_color(BLUE);
     for(i =0;i<lcd.Get_Display_Width();i+=5)
    {
      lcd.Draw_Fast_VLine(i,0,lcd.Get_Display_Height()); 
           delay(5);
    }
}

//draw some rectangles
void rectangle_test(void)
{
  int i = 0;
   lcd.Fill_Screen(BLACK);
     lcd.Set_Draw_color(GREEN);
   for(i = 0;i<lcd.Get_Display_Width()/2;i+=4)
   {
      lcd.Draw_Rectangle(i,(lcd.Get_Display_Height()-lcd.Get_Display_Width())/2+i,lcd.Get_Display_Width()-1-i,lcd.Get_Display_Height()-(lcd.Get_Display_Height()-lcd.Get_Display_Width())/2-i);  
        delay(5);
   }
}

//draw some filled rectangles
void fill_rectangle_test(void)
{
  int i = 0;
   lcd.Fill_Screen(BLACK);
     lcd.Set_Draw_color(YELLOW);
   lcd.Fill_Rectangle(0,(lcd.Get_Display_Height()-lcd.Get_Display_Width())/2,lcd.Get_Display_Width()-1,lcd.Get_Display_Height()-(lcd.Get_Display_Height()-lcd.Get_Display_Width())/2);
    lcd.Set_Draw_color(MAGENTA);
   for(i = 0;i<lcd.Get_Display_Width()/2;i+=4)
   {
      lcd.Draw_Rectangle(i,(lcd.Get_Display_Height()-lcd.Get_Display_Width())/2+i,lcd.Get_Display_Width()-1-i,lcd.Get_Display_Height()-(lcd.Get_Display_Height()-lcd.Get_Display_Width())/2-i);  
        delay(5);
   }
   for(i = 0;i<lcd.Get_Display_Width()/2;i+=4)
   {
       lcd.Set_Draw_color(random(255), random(255), random(255));
      lcd.Fill_Rectangle(i,(lcd.Get_Display_Height()-lcd.Get_Display_Width())/2+i,lcd.Get_Display_Width()-1-i,lcd.Get_Display_Height()-(lcd.Get_Display_Height()-lcd.Get_Display_Width())/2-i);  
        delay(5);
   }
}

//draw some filled circles
void fill_circles_test(void)
{
  int r=10,i=0,j=0;
  lcd.Fill_Screen(BLACK);
   lcd.Set_Draw_color(MAGENTA);
  for(i=r;i<lcd.Get_Display_Width();i+=2*r)
  {
    for(j=r;j<lcd.Get_Display_Height();j+=2*r)
    {
      lcd.Fill_Circle(i, j, r);
    }
  }
}

//draw some circles
void circles_test(void)
{
  int r=10,i=0,j=0;
   lcd.Set_Draw_color(GREEN);
  for(i=0;i<lcd.Get_Display_Width()+r;i+=2*r)
  {
    for(j=0;j<lcd.Get_Display_Height()+r;j+=2*r)
    {
      lcd.Draw_Circle(i, j, r);
    }
  }  
}

//draw some triangles
void triangles_test(void)
{
   int i = 0;
   lcd.Fill_Screen(BLACK);
   for(i=0;i<lcd.Get_Display_Width()/2;i+=5)
   {
      lcd.Set_Draw_color(0,i+64,i+64);
      lcd.Draw_Triangle(lcd.Get_Display_Width()/2-1,lcd.Get_Display_Height()/2-1-i,
                    lcd.Get_Display_Width()/2-1-i,lcd.Get_Display_Height()/2-1+i,
                    lcd.Get_Display_Width()/2-1+i,lcd.Get_Display_Height()/2-1+i);                   
   }
}

//draw some filled triangles
void fill_triangles_test(void)
{
   int i = 0;
   lcd.Fill_Screen(BLACK);
    for(i=lcd.Get_Display_Width()/2-1;i>0;i-=5)
   {
    
      lcd.Set_Draw_color(0,i+64,i+64);
      lcd.Fill_Triangle(lcd.Get_Display_Width()/2-1,lcd.Get_Display_Height()/2-1-i,
                    lcd.Get_Display_Width()/2-1-i,lcd.Get_Display_Height()/2-1+i,
                    lcd.Get_Display_Width()/2-1+i,lcd.Get_Display_Height()/2-1+i);                   
      lcd.Set_Draw_color(i,0,i);
      lcd.Draw_Triangle(lcd.Get_Display_Width()/2-1,lcd.Get_Display_Height()/2-1-i,
                    lcd.Get_Display_Width()/2-1-i,lcd.Get_Display_Height()/2-1+i,
                    lcd.Get_Display_Width()/2-1+i,lcd.Get_Display_Height()/2-1+i);                   
   }
}

//draw some round rectangles
void round_rectangle(void)
{
   int i = 0;
   lcd.Fill_Screen(BLACK);
     for(i = 0;i<lcd.Get_Display_Width()/2;i+=4)
   {
       lcd.Set_Draw_color(255-i,0,160-i);
      lcd.Draw_Round_Rectangle(i,(lcd.Get_Display_Height()-lcd.Get_Display_Width())/2+i,lcd.Get_Display_Width()-1-i,lcd.Get_Display_Height()-(lcd.Get_Display_Height()-lcd.Get_Display_Width())/2-i,8);
        delay(5);
   } 
}

//draw some filled round rectangles
void fill_round_rectangle(void)
{
     int i = 0;
   lcd.Fill_Screen(BLACK);
     for(i = 0;i<lcd.Get_Display_Width()/2;i+=4)
   {
       lcd.Set_Draw_color(255-i,160-i,0);
      lcd.Fill_Round_Rectangle(i,(lcd.Get_Display_Height()-lcd.Get_Display_Width())/2+i,lcd.Get_Display_Width()-1-i,lcd.Get_Display_Height()-(lcd.Get_Display_Height()-lcd.Get_Display_Width())/2-i,8);
        delay(5);
   } 
}

void setup() 
{
  lcd.Init_LCD();
  fill_screen_test();
  delay(500);
  text_test();
  delay(500);
  lines_test();
  delay(500);
  h_l_lines_test();
  delay(500);
  rectangle_test();
  delay(500);
  fill_rectangle_test();
  delay(500);
  fill_circles_test();
  delay(500);
  circles_test();
  delay(500);
  triangles_test();
  delay(500);
  fill_triangles_test();
  delay(500);
   round_rectangle();
   delay(500);
   fill_round_rectangle();
   delay(3000);
}

void loop() 
{
  //rotate for four directions
 for(uint8_t rotation=0; rotation<4; rotation++) 
 {
    lcd.Set_Rotation(rotation);
    text_test();
    delay(2000);
 }
}
