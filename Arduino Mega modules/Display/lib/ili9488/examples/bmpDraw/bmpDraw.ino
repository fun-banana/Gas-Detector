//===============================================
//                   Example3_7
//===============================================
#include <SdFat.h>
#include <SPI.h>

#include "ili9488.h"
#include "bitmap.h"

#define SD_CS 48

void setup() {
  SdFat sd;

  lcd.Init_LCD();
  lcd.Set_Rotation(3);  
  lcd.Fill_Screen(BLACK); 
  lcd.Print("Initializing SD card...", 0, 0);
    if (!sd.begin(SD_CS, SPI_FULL_SPEED)) 
         lcd.Print("failed!", 0, 10);
   else
         lcd.Print("OK!", 0, 10);
     delay(1000);
     lcd.Fill_Screen(WHITE); 
    
     bmp::draw("colors.bmp", 0, 0);

}//End of setup function 


void loop() {
    }//End of loop function 

//===============================================
//         End Of File "Example3_7"        
//===============================================

