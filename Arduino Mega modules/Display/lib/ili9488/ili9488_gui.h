#ifndef _ILI9488_GUI_H_
#define _LCDWIKI_GUI_H_

#include <WString.h>
#include <stdint.h>
   
#define RIGHT  9999  
#define CENTER 9998 
#define LEFT   0   

class ILI9488_GUI
{
public:
	/*VIRTUAL_FUNCTIONS_START*/
	virtual int16_t  Read_GRAM(int16_t x, int16_t y, uint16_t *block, int16_t w, int16_t h) = 0;

	virtual void     Push_Any_Color(uint16_t* block, int16_t n, bool first, uint8_t flags) = 0;
	virtual void     Fill_Rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) = 0;
	virtual void     Set_Addr_Window(int16_t x1, int16_t y1, int16_t x2, int16_t y2) = 0;
	virtual void     Draw_Pixe(int16_t x, int16_t y, uint16_t color) = 0;
	virtual uint16_t Color_To_565(uint8_t r, uint8_t g, uint8_t b) = 0;

	virtual int16_t  Get_Height() const = 0;
  	virtual int16_t  Get_Width()  const = 0;
	/*VIRTUAL_FUNCTIONS_END*/

	/*PRINT_FUNCTIONS_START*/
	void   Print_Number_Float(double num, uint8_t dec, int16_t x, int16_t y, uint8_t divider, int16_t length, uint8_t filler);

	void   Print_Number_Int(long num, int16_t x, int16_t y, int16_t length, uint8_t filler, int16_t system);

	void   Print_String(const uint8_t *st, int16_t x, int16_t y) { Print((uint8_t *)st, x, y);           }
	void   Print_String(uint8_t *st, int16_t x, int16_t y)       { Print(st, x, y);                      }
	void   Print_String(String st, int16_t x, int16_t y)         { Print((uint8_t *)(st.c_str()), x, y); }
	size_t Print(uint8_t *st, int16_t x, int16_t y);

	size_t write(uint8_t c);
	/*PRINT_FUNCTIONS_END*/

	/*TEXT_FUNCTIONS_START*/
	void     Set_Text_Back_colour(uint8_t r, uint8_t g, uint8_t b) { text_bgcolor = Color_To_565(r, g, b); }
	void     Set_Text_Back_colour(uint16_t color)                  { text_bgcolor = color;                 }
	uint16_t Get_Text_Back_colour() const                          { return text_bgcolor;                  }

	void     Set_Text_colour(uint8_t r, uint8_t g, uint8_t b) { text_color = Color_To_565(r, g, b); }
	void     Set_Text_colour(uint16_t color)                  { text_color = color;                 }
	uint16_t Get_Text_colour() const                          { return text_color;                  }

	void     Set_Text_Cousur(int16_t x, int16_t y) { text_x = x; text_y = y; }
	int16_t  Get_Text_X_Cousur() const             { return text_x; }
	int16_t  Get_Text_Y_Cousur() const             { return text_y; }

	void     Set_Text_Size(uint8_t size) { text_size = size; }
	uint8_t  Get_Text_Size() const       { return text_size; }

	void     Set_Text_Mode(bool mode) { text_mode = mode; }
	bool     Get_Text_Mode() const    { return text_mode; }
	/*TEXT_FUNCTIONS_END*/


	/*DRAW_FUNCTIONS_START*/
	void     Draw_Char(int16_t x, int16_t y, uint8_t c, uint16_t color, uint16_t bg, uint8_t size, bool mode);

	void     Draw_Bit_Map(int16_t x, int16_t y, int16_t sx, int16_t sy, const uint16_t *data, int16_t scale);

	void     Draw_Triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2);

	void     Draw_Round_Rectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t radius);
	void     Draw_Rectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2);

	void     Draw_Circle_Helper(int16_t x0, int16_t y0, int16_t radius, uint8_t cornername);
	void     Draw_Circle(int16_t x, int16_t y, int16_t radius);

	void     Draw_Line(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
	void     Draw_Fast_HLine(int16_t x, int16_t y, int16_t w) { Fill_Rect(x, y, w, 1, draw_color); }
	void     Draw_Fast_VLine(int16_t x, int16_t y, int16_t h) { Fill_Rect(x, y, 1, h, draw_color); }
	void     Draw_Pixel(int16_t x, int16_t y)                 { Draw_Pixe(x, y, draw_color);       }

	void     Set_Draw_color(uint8_t r, uint8_t g, uint8_t b) { draw_color = Color_To_565(r, g, b); }
	void     Set_Draw_color(uint16_t color)                  { draw_color = color;                 }
	uint16_t Get_Draw_color() const                          { return draw_color;                  }
	/*DRAW_FUNCTIONS_END*/

	/*FILL_FUNCTIONS_START*/
	void Fill_Circle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta);
	void Fill_Circle(int16_t x, int16_t y, int16_t radius);

	void Fill_Triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2);

	void Fill_Round_Rectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t radius);
	void Fill_Rectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2);

	void Fill_Screen(uint8_t r, uint8_t g, uint8_t b);
	void Fill_Screen(uint16_t color) { Fill_Rect(0, 0, Get_Width(), Get_Height(), color); }
	/*FILL_FUNCTIONS_END*/
	
	uint16_t Read_Pixel(int16_t x, int16_t y);

	int16_t  Get_Display_Height() const { return Get_Height(); }
	int16_t  Get_Display_Width() const  { return Get_Width();  }
	
protected:
	uint16_t text_bgcolor{ 0xF800 };
	uint16_t text_color  { 0x07E0 };
	uint16_t draw_color  { 0xF800 };
	uint8_t  text_size   {      1 };
	bool     text_mode   {      0 };

	int16_t  text_x;
	int16_t  text_y;
};

#endif