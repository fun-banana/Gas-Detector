// Lcdwiki GUI library with init code from Rossum
// MIT license

#ifndef _ILI9488_H_
#define _ILI9488_H_

#include <avr/pgmspace.h>
#include <stdint.h>

#include "ili9488_gui.h"

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

class ILI9488 : public ILI9488_GUI
{
public:
	ILI9488();

	/*OVERWRITTEN_FUNCTIONS_START*/
	int16_t  Read_GRAM(int16_t x, int16_t y, uint16_t *block, int16_t w, int16_t h) override;

	void     Push_Any_Color(uint16_t * block, int16_t n, bool first, uint8_t flags) override;
	void     Fill_Rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
	void     Set_Addr_Window(int16_t x1, int16_t y1, int16_t x2, int16_t y2) override;
	void     Draw_Pixe(int16_t x, int16_t y, uint16_t color) override;
	uint16_t Color_To_565(uint8_t r, uint8_t g, uint8_t b) override;

	int16_t Get_Height() const override { return height; }
	int16_t Get_Width() const  override { return width;  }
	/*OVERWRITTEN_FUNCTIONS_END*/

	void Push_Any_Color(uint8_t * block, int16_t n, bool first, uint8_t flags);

	void Vert_Scroll(int16_t top, int16_t scrollines, int16_t offset);

	void Push_Command(uint16_t cmd, uint8_t *block, int8_t N);

	void init_table8(const void *table, int16_t size);

	uint8_t Get_Rotation() const { return rotation; }
	void    Set_Rotation(uint8_t r); 
	
	void Invert_Display(bool i);

	void Init_LCD();

	void reset();

	void start();

protected:
    uint16_t width, height, rotation;		
	volatile uint8_t *csPort	, *cdPort	 , *wrPort	  , *rdPort;
	uint8_t 		  csPinSet	,  cdPinSet  ,	wrPinSet  ,  rdPinSet  ,
	                  csPinUnset,  cdPinUnset,	wrPinUnset,  rdPinUnset,
					  _reset;	  
};

extern ILI9488 lcd;

#endif