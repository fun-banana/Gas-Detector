// IMPORTANT: LIBRARY MUST BE SPECIFICALLY CONFIGURED FOR EITHER TFT SHIELD
// OR BREAKOUT BOARD USAGE.

// Lcdwiki TOUCH library
// MIT license


#ifndef _ILI9488_TOUCH_H_
#define _ILI9488_TOUCH_H_

#include <stdint.h>

class ILI9488_TOUCH
{
  public:
	ILI9488_TOUCH();

	void TP_Init();

	uint8_t TP_Scan();

	uint16_t getX() const { return x; }
	uint16_t getY() const { return y; }
	
  private:
		volatile uint8_t *tcsPort, *tclkPort, *tdoutPort, *tdinPort, *tirqPort;
		uint8_t  tcsPinSet, tclkPinSet,	tdoutPinSet, tdinPinSet, tirqPinSet;
		uint8_t touch_statue;
		uint16_t x, y;

		uint8_t  TP_Read_Coordinate2(uint16_t *x, uint16_t *y);
		uint8_t  TP_Read_Coordinate(uint16_t *x, uint16_t *y);
		uint16_t TP_Read_XY(uint8_t xy);

		void     TP_Write_Byte(uint8_t data);
		uint16_t TP_Read_ADC(uint8_t cmd);
};

extern ILI9488_TOUCH lcdT;

#endif
