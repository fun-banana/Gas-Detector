// IMPORTANT: LIBRARY MUST BE SPECIFICALLY CONFIGURED FOR EITHER TFT SHIELD
// OR BREAKOUT BOARD USAGE.

// Lcdwiki GUI library
// MIT license

#include "pins_arduino.h"
#include "wiring_private.h"

#include "ili9488.h"

/*8 bit magic*/
#define DELAY7        \
  asm volatile(       \
    "rjmp .+0" "\n\t" \
    "rjmp .+0" "\n\t" \
    "rjmp .+0" "\n\t" \
    "nop"      "\n"   \
    ::);

 // When using the TFT breakout board, control pins are configurable.
#define RD_ACTIVE  *rdPort &=  rdPinUnset
#define RD_IDLE    *rdPort |=  rdPinSet
#define WR_ACTIVE  *wrPort &=  wrPinUnset
#define WR_IDLE    *wrPort |=  wrPinSet
#define CD_COMMAND *cdPort &=  cdPinUnset
#define CD_DATA    *cdPort |=  cdPinSet
#define CS_ACTIVE  *csPort &=  csPinUnset
#define CS_IDLE    *csPort |=  csPinSet

#define CMASK    0xFF
#define write8(d) {\
		PORTC = d;WR_STROBE;}
#define read8(dst) {\
  		RD_ACTIVE; DELAY7; \
  		dst = PINC;RD_IDLE;}
#define setWriteDir() {DDRC |= CMASK;}
#define setReadDir()  {DDRC &= ~CMASK;}

// Data write strobe, ~2 instructions and always inline
#define WR_STROBE { WR_ACTIVE; WR_IDLE; }
#define write16(d) { uint8_t h = (d)>>8, l = d; write8(h); write8(l); }
#define writeCmd8(x){ CD_COMMAND; write8(x); CD_DATA;  }
#define writeData8(x){  write8(x) }
#define writeCmd16(x){ CD_COMMAND; write16(x); CD_DATA; }
#define writeData16(x){ write16(x) }

// These higher-level operations are usually functionalized,
// except on Mega where's there's gobs and gobs of program space.

// Set value of TFT register: 8-bit address, 8-bit value
#define writeCmdData8(a, d) { CD_COMMAND; write8(a); CD_DATA; write8(d); }

// Set value of TFT register: 16-bit address, 16-bit value
// See notes at top about macro expansion, hence hi & lo temp vars
#define writeCmdData16(a, d) { \
  uint8_t hi, lo; \
  hi = (a) >> 8; lo = (a); CD_COMMAND; write8(hi); write8(lo); \
  hi = (d) >> 8; lo = (d); CD_DATA   ; write8(hi); write8(lo); }
/*8 bit magic*/

#define HX8347G_COLADDREND_HI      0x04
#define HX8347G_COLADDREND_LO      0x05
#define HX8347G_ROWADDREND_HI      0x08
#define HX8347G_ROWADDREND_LO      0x09
#define HX8357_RAMRD               0x2E

#define ILI9488_COLADDRSET         0x2A
#define ILI9488_PAGEADDRSET        0x2B
#define ILI9488_MEMORYWRITE        0x2C

#define ILI9488_MADCTL     0x36
#define ILI9488_MADCTL_MY  0x80
#define ILI9488_MADCTL_MX  0x40
#define ILI9488_MADCTL_MV  0x20
#define ILI9488_MADCTL_ML  0x10
#define ILI9488_MADCTL_BGR 0x08

#define TFTLCD_DELAY16  0xFFFF
#define TFTLCD_DELAY8   0x7F
#define MAX_REG_NUM     24

#define HEIGHT 480
#define WIDTH  320

#define RD    43
#define RESET 41
#define CS    40
#define CD    38
#define WR    39

ILI9488::ILI9488()
{
	_reset = RESET;

	csPort = portOutputRegister(digitalPinToPort(CS));
	cdPort = portOutputRegister(digitalPinToPort(CD));
	wrPort = portOutputRegister(digitalPinToPort(WR));
	rdPort = portOutputRegister(digitalPinToPort(RD));

	csPinSet = digitalPinToBitMask(CS);
	cdPinSet = digitalPinToBitMask(CD);
	wrPinSet = digitalPinToBitMask(WR);
	rdPinSet = digitalPinToBitMask(RD);

	csPinUnset = ~csPinSet;
	cdPinUnset = ~cdPinSet;
	wrPinUnset = ~wrPinSet;
	rdPinUnset = ~rdPinSet;

	*csPort |= csPinSet;
	*cdPort |= cdPinSet;
	*wrPort |= wrPinSet;
	*rdPort |= rdPinSet;

	pinMode(CS, OUTPUT);
	pinMode(CD, OUTPUT);
	pinMode(WR, OUTPUT);
	pinMode(RD, OUTPUT);

	digitalWrite(RESET, HIGH);
	pinMode(RESET, OUTPUT);

	rotation = 0;
	setWriteDir();
	width = WIDTH;
	height = HEIGHT;
}

int16_t ILI9488::Read_GRAM(int16_t x, int16_t y, uint16_t *block, int16_t w, int16_t h)
{
	uint16_t ret, dummy;
	int16_t n = w * h;
	uint8_t r, g, b, tmp;
	Set_Addr_Window(x, y, x + w - 1, y + h - 1);
	while (n > 0)
	{
		CS_ACTIVE;
		writeCmd16(HX8357_RAMRD);
		setReadDir();
		read8(r);
		while (n)
		{
			read8(r);
			read8(g);
			read8(b);
			ret = Color_To_565(r, g, b);
			*block++ = ret;
			n--;
		}
		CS_IDLE;
		setWriteDir();
	}
	return 0;
}

void ILI9488::Push_Any_Color(uint16_t* block, int16_t n, bool first, uint8_t flags)
{
	uint16_t color;
	uint8_t h, l;
	bool isconst = flags & 1;
	CS_ACTIVE;
	if (first)
	{
		writeCmd8(ILI9488_MEMORYWRITE);
	}
	while (n-- > 0)
	{
		if (isconst)
		{
			color = pgm_read_word(block++);
		}
		else
		{
			color = (*block++);

		}
		writeData16(color);
	}
	CS_IDLE;
}

void ILI9488::Fill_Rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	int16_t end;
	if (w < 0)
	{
		w = -w;
		x -= w;
	}                           //+ve w
	end = x + w;
	if (x < 0)
	{
		x = 0;
	}
	if (end > Get_Width())
	{
		end = Get_Width();
	}
	w = end - x;
	if (h < 0)
	{
		h = -h;
		y -= h;
	}                           //+ve h
	end = y + h;
	if (y < 0)
	{
		y = 0;
	}
	if (end > Get_Height())
	{
		end = Get_Height();
	}
	h = end - y;
	Set_Addr_Window(x, y, x + w - 1, y + h - 1);//set area
	CS_ACTIVE;
	writeCmd8(ILI9488_MEMORYWRITE);
	if (h > w)
	{
		end = h;
		h = w;
		w = end;
	}
	while (h-- > 0)
	{
		end = w;
		do
		{
			writeData16(color);//set color data
		} while (--end != 0);
	}
	CS_IDLE;
}

void ILI9488::Set_Addr_Window(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	CS_ACTIVE;
	uint8_t x_buf[] = { x1 >> 8,x1 & 0xFF,x2 >> 8,x2 & 0xFF };
	uint8_t y_buf[] = { y1 >> 8,y1 & 0xFF,y2 >> 8,y2 & 0xFF };
	Push_Command(ILI9488_COLADDRSET, x_buf, 4); //set x address
	Push_Command(ILI9488_PAGEADDRSET, y_buf, 4); //set y address
	CS_IDLE;
}

void ILI9488::Draw_Pixe(int16_t x, int16_t y, uint16_t color)
{
	if ((x < 0) || (y < 0) || (x > Get_Width()) || (y > Get_Height()))
	{
		return;
	}
	Set_Addr_Window(x, y, x, y);
	CS_ACTIVE;
	writeCmdData16(ILI9488_MEMORYWRITE, color);
	CS_IDLE;
}

uint16_t ILI9488::Color_To_565(uint8_t r, uint8_t g, uint8_t b)
{
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
}

void ILI9488::Push_Any_Color(uint8_t* block, int16_t n, bool first, uint8_t flags)
{
	uint16_t color;
	uint8_t h, l;
	bool isconst = flags & 1;
	bool isbigend = (flags & 2) != 0;
	CS_ACTIVE;
	if (first)
	{
		writeCmd8(ILI9488_MEMORYWRITE);
	}
	while (n-- > 0)
	{
		if (isconst)
		{
			h = pgm_read_byte(block++);
			l = pgm_read_byte(block++);
		}
		else
		{
			h = (*block++);
			l = (*block++);
		}
		color = (isbigend) ? (h << 8 | l) : (l << 8 | h);
		writeData16(color);
	}
	CS_IDLE;
}

void ILI9488::Vert_Scroll(int16_t top, int16_t scrollines, int16_t offset)
{
	int16_t bfa = HEIGHT - top - scrollines;
	int16_t vsp;
	int16_t sea = top;
	if (offset <= -scrollines || offset >= scrollines)
	{
		offset = 0; //valid scroll
	}
	vsp = top + offset; // vertical start position
	if (offset < 0)
	{
		vsp += scrollines;          //keep in unsigned range
	}
	sea = top + scrollines - 1;
	uint8_t d[6];           // for multi-byte parameters
	d[0] = top >> 8;        //TFA
	d[1] = top;
	d[2] = scrollines >> 8; //VSA
	d[3] = scrollines;
	d[4] = bfa >> 8;        //BFA
	d[5] = bfa;
	Push_Command(0x33, d, 6);
	d[0] = vsp >> 8;        //VSP
	d[1] = vsp;
	Push_Command(0x37, d, 2);
	if (offset == 0)
	{
		Push_Command(0x13, NULL, 0);
	}
}

void ILI9488::Push_Command(uint16_t cmd, uint8_t *block, int8_t N)
{
	CS_ACTIVE;
	writeCmd16(cmd);
	while (N-- > 0)
	{
		uint8_t u8 = *block++;
		writeData8(u8);
	}
	CS_IDLE;
}

void ILI9488::init_table8(const void *table, int16_t size)
{
	uint8_t* p = (uint8_t*)table;
	uint8_t  dat[MAX_REG_NUM];
	while (size > 0)
	{
		uint8_t cmd = pgm_read_byte(p++);
		uint8_t len = pgm_read_byte(p++);
		if (cmd == TFTLCD_DELAY8)
		{
			delay(len);
			len = 0;
		}
		else
		{
			for (uint8_t i = 0; i < len; i++)
			{
				dat[i] = pgm_read_byte(p++);
			}
			Push_Command(cmd, dat, len);
		}
		size -= len + 2;
	}
}

void ILI9488::Set_Rotation(uint8_t r)
{
	rotation = r & 3;           // just perform the operation ourselves on the protected variables
	width = (rotation & 1) ? HEIGHT : WIDTH;
	height = (rotation & 1) ? WIDTH : HEIGHT;
	CS_ACTIVE;
	uint8_t val;
	switch (rotation)
	{
	case 0:
		val = ILI9488_MADCTL_MX | ILI9488_MADCTL_MY | ILI9488_MADCTL_BGR; //0 degree 
		break;
	case 1:
		val = ILI9488_MADCTL_MV | ILI9488_MADCTL_MY | ILI9488_MADCTL_BGR; //90 degree 
		break;
	case 2:
		val = ILI9488_MADCTL_ML | ILI9488_MADCTL_BGR; //180 degree 
		break;
	case 3:
		val = ILI9488_MADCTL_MX | ILI9488_MADCTL_ML | ILI9488_MADCTL_MV | ILI9488_MADCTL_BGR; //270 degree
		break;
	}
	writeCmdData8(ILI9488_MADCTL, val);
	Set_Addr_Window(0, 0, width - 1, height - 1);
	Vert_Scroll(0, HEIGHT, 0);
	CS_IDLE;
}

void ILI9488::Invert_Display(bool i)
{
	CS_ACTIVE;
	uint8_t val = 0 ^ i;
	writeCmd8(val ? 0x21 : 0x20);
	CS_IDLE;
}

void ILI9488::Init_LCD()
{
	reset();
	start();
}

void ILI9488::reset()
{
	CS_IDLE;
	RD_IDLE;
	WR_IDLE;
	if (_reset)
	{
		digitalWrite(_reset, LOW);
		delay(2);
		digitalWrite(_reset, HIGH);
	}
	CS_ACTIVE;
	CD_COMMAND;
	write8(0x00);
	for (uint8_t i = 0; i < 3; i++)
	{
		WR_STROBE;
	}
	CS_IDLE;
}

void ILI9488::start()
{
	reset();
	delay(200);

	static const uint8_t ILI9488_regValues[] PROGMEM =
	{
		0xF7, 4, 0xA9, 0x51, 0x2C, 0x82,
		0xC0, 2, 0x11, 0x09,
		0xC1, 1, 0x41,
		0xC5, 3, 0x00, 0x0A, 0x80,
		0xB1, 2, 0xB0, 0x11,
		0xB4, 1, 0x02,
		0xB6, 2, 0x02, 0x22,
		0xB7, 1, 0xC6,
		0xBE, 2, 0x00, 0x04,
		0xE9, 1, 0x00,
		0x36, 1, 0x08,
		0x3A, 1, 0x55,
		0xE0, 15, 0x00, 0x07, 0x10, 0x09, 0x17, 0x0B, 0x41, 0x89, 0x4B, 0x0A, 0x0C, 0x0E, 0x18, 0x1B, 0x0F,
		0xE1, 15, 0x00, 0x17, 0x1A, 0x04, 0x0E, 0x06, 0x2F, 0x45, 0x43, 0x02, 0x0A, 0x09, 0x32, 0x36, 0x0F,
		0x11, 0,
		TFTLCD_DELAY8, 120,
		0x29, 0
	};

	init_table8(ILI9488_regValues, sizeof(ILI9488_regValues));
	Set_Rotation(rotation);
	Invert_Display(false);
}

ILI9488 lcd;