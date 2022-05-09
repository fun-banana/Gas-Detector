#include <Arduino.h>
#include <ili9488.h>

class Lcd
{
    private:
        bool _isAlreadyDrawWarning;
        bool _isAlreadyDrawOk;

    public:
        void Setup()
        {
            lcd.Init_LCD();
            lcd.Fill_Screen(BLACK);
            lcd.Set_Text_Size(3);
            lcd.Set_Rotation(3);
            _isAlreadyDrawOk = false;
            _isAlreadyDrawWarning = false;
        }

        void PrintDisplayStartInfo()
        {
            PrintLines();
            lcd.Set_Text_colour(GREEN);
            lcd.Set_Text_Back_colour(BLACK);
            lcd.Print("FINAL PROJECT\n",120,80);
            lcd.Print("Gas Detector system",60,110);
            lcd.Print("Danil and Misha",110,200);
        }

        void PrintOkayStatus()
        {
            if (!_isAlreadyDrawOk)
            {
                Clear();
                PrintLines();
                lcd.Set_Text_colour(GREEN);
                lcd.Set_Text_Back_colour(BLACK);
                lcd.Print("Gas Detector Status",60,110);
                lcd.Print("Okay",200,200);
                _isAlreadyDrawOk = true;
                _isAlreadyDrawWarning = false;
            }
        }

        void PrintWarningStatus()
        {
            if (!_isAlreadyDrawWarning)
            {
                Clear();
                PrintLines();
                lcd.Set_Text_colour(RED);
                lcd.Set_Text_Back_colour(BLACK);
                lcd.Print("Gas Detector Status",60,110);
                lcd.Print("Warning",190,200);
                _isAlreadyDrawWarning = true;
                _isAlreadyDrawOk = false;
            }
        }

        void Clear()
        {
            lcd.Fill_Screen(BLACK);
        }

    private:
        void PrintLines()
        {
            lcd.Set_Draw_color(WHITE);
            lcd.Draw_Line(0,40,480,40);
            lcd.Draw_Line(0,280,480,280);
        }
};