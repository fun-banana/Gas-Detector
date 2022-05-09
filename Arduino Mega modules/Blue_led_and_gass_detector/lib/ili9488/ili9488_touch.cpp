// IMPORTANT: LIBRARY MUST BE SPECIFICALLY CONFIGURED FOR EITHER TFT SHIELD
// OR BREAKOUT BOARD USAGE.

// Lcdwiki TOUCH library
// MIT license


#include "ili9488_touch.h"
#include "ili9488.h"

#include <Arduino.h>

#define swap(a, b) { int16_t t = a; a = b; b = t; }

#define TCLK_LOW 		*tclkPort &= ~tclkPinSet
#define TCLK_HIGH   	*tclkPort |= tclkPinSet
#define TCS_LOW  		*tcsPort &= ~tcsPinSet
#define TCS_HIGH    	*tcsPort |= tcsPinSet
#define TDIN_LOW  		*tdinPort &= ~tdinPinSet
#define TDIN_HIGH		*tdinPort |= tdinPinSet
#define TDOUT_STATE 	((*tdoutPort) & tdoutPinSet)
#define TIRQ_STATE		((*tirqPort) & tirqPinSet)

#define XFAC      852 //663 
#define XOFFSET   (-14) //(-13) 
#define YFAC      1284 //894 
#define YOFFSET   (-30) 

#define CMD_RDX 0XD0
#define CMD_RDY 0X90

#define TP_PRES_DOWN 0x80  
#define TP_CATH_PRES 0x40  

#define HEIGHT 480
#define WIDTH  320

#define T_CS   53
#define T_CLK  52
#define T_DIN  51
#define T_DOUT 50
#define T_IRQ  44
 			    			
ILI9488_TOUCH::ILI9488_TOUCH()
{
	tcsPort	 = portOutputRegister(digitalPinToPort(T_CS));
	tclkPort = portOutputRegister(digitalPinToPort(T_CLK));
	tdoutPort = portInputRegister(digitalPinToPort(T_DOUT));
	tdinPort = portOutputRegister(digitalPinToPort(T_DIN));
	tirqPort = portInputRegister(digitalPinToPort(T_IRQ));

	tcsPinSet  = digitalPinToBitMask(T_CS);
	tclkPinSet = digitalPinToBitMask(T_CLK);
	tdoutPinSet = digitalPinToBitMask(T_DOUT);
	tdinPinSet = digitalPinToBitMask(T_DIN);
	tirqPinSet = digitalPinToBitMask(T_IRQ);
	
	pinMode(T_CS, OUTPUT);
	pinMode(T_CLK, OUTPUT);
	pinMode(T_DOUT, INPUT);
	pinMode(T_DIN, OUTPUT);
	pinMode(T_IRQ, INPUT);

	touch_statue = 0 ;
	x=0xffff;
	y=0xffff;
}

void ILI9488_TOUCH::TP_Init()
{
	TDIN_HIGH;
	TCLK_HIGH; 
	TCS_HIGH;
}

uint8_t ILI9488_TOUCH::TP_Scan()
{
	if (TIRQ_STATE == 0)
	{
		if (TP_Read_Coordinate2(&x, &y))
		{
			x = ((long)XFAC*x) / 10000 + XOFFSET;
			y = ((long)YFAC*y) / 10000 + YOFFSET;
			uint8_t rotation = lcd.Get_Rotation();
			uint16_t height = (rotation & 1) ? WIDTH : HEIGHT;
			uint16_t width = (rotation & 1) ? HEIGHT : WIDTH;

			if (rotation == 0) {
				x = width - x;
			}
			else if (rotation == 1) {
				swap(x, y);
			}
			else if (rotation == 2) {
				y = height - y;
			}
			else if (rotation == 3) {
				swap(x, y);
				y = height - y;
				x = width - x;
			}

			if (x < 0) {
				x = 0;
			}
			if (x > width) {
				x = width;
			}
			if (y < 0) {
				y = 0;
			}
			if (y > height) {
				y = height;
			}
		}
		if ((touch_statue & TP_PRES_DOWN) == 0)
		{
			touch_statue = TP_PRES_DOWN | TP_CATH_PRES;
		}
	}
	else
	{
		if (touch_statue & TP_PRES_DOWN)
		{
			touch_statue &= ~(1 << 7);
		}
		else
		{
			x = 0xffff;
			y = 0xffff;
		}
	}
	return touch_statue & TP_PRES_DOWN;
}

#define ERR_RANGE 50

uint8_t ILI9488_TOUCH::TP_Read_Coordinate2(uint16_t *x,uint16_t *y)
{
  	uint16_t x1,y1;
  	uint16_t x2,y2;
  	uint8_t flag;    
    flag=TP_Read_Coordinate(&x1,&y1);  
    if(flag==0)
    {
		return 0;
    }
	flag=TP_Read_Coordinate(&x2,&y2);
    if(flag==0)
    {
		return 0;   
    }
	if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//Before and after the two samples are within +- ERR_RANGE.
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }
	else
	{
      	return 0;          
  	}        
} 

uint8_t ILI9488_TOUCH::TP_Read_Coordinate(uint16_t *x, uint16_t *y)
{
	uint16_t xtemp, ytemp;
	xtemp = TP_Read_XY(CMD_RDX);
	ytemp = TP_Read_XY(CMD_RDY);
	*x = xtemp;
	*y = ytemp;
	return 1;//Reading success
}

#define READ_TIMES 5 
#define LOST_VAL 1          

uint16_t ILI9488_TOUCH::TP_Read_XY(uint8_t xy)
{
	uint16_t i, j;
	uint16_t buf[READ_TIMES];
	uint16_t sum = 0;
	uint16_t temp;
	for (i = 0; i < READ_TIMES; i++)
	{
		buf[i] = TP_Read_ADC(xy);
	}
	for (i = 0; i < READ_TIMES - 1; i++)//Sort in ascending order
	{
		for (j = i + 1; j < READ_TIMES; j++)
		{
			if (buf[i] > buf[j])
			{
				temp = buf[i];
				buf[i] = buf[j];
				buf[j] = temp;
			}
		}
	}
	for (i = LOST_VAL; i < READ_TIMES - LOST_VAL; i++) //Remove maximum and minimum values
	{
		sum += buf[i];
	}
	temp = sum / (READ_TIMES - 2 * LOST_VAL);
	return temp;
}

void ILI9488_TOUCH::TP_Write_Byte(uint8_t data)
{
	uint8_t val = 0x80;
	while (val)
	{
		if (data&val)
		{
			TDIN_HIGH;
		}
		else
		{
			TDIN_LOW;
		}
		TCLK_LOW;
		TCLK_HIGH;
		val >>= 1;
	}
}

uint16_t ILI9488_TOUCH::TP_Read_ADC(uint8_t cmd)
{
	uint16_t num = 0;
	uint8_t count = 0;
	TCS_LOW;
	TCLK_LOW;
	TDIN_LOW;
	TP_Write_Byte(cmd);
	TCLK_LOW;
	delayMicroseconds(1);
	TCLK_HIGH;
	TCLK_LOW;
	for (count = 0; count < 16; count++)
	{
		num <<= 1;
		TCLK_LOW;
		TCLK_HIGH;
		if (TDOUT_STATE)
		{
			num += 1;
		}
		else
		{
			num += 0;
		}
	}
	num >>= 4;   // the high 12 bits is valid
	TCS_HIGH;
	return num;
}

ILI9488_TOUCH lcdT;