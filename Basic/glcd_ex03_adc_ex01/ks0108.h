/*
 * Copyright:      Fabian Maximilian Thiele  mailto:me@apetech.de
 * Author:         Fabian Maximilian Thiele
 * Remarks:        this Copyright must be included
 * known Problems: none
 * Version:        1.1
 * Description:    Graphic Library for KS0108- (and compatible) based LCDs
 *
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef	KS0108_H
#define KS0108_H

// Ports
#define LCD_CMD_PORT		PORTC		// Command Output Register
#define LCD_CMD_DIR			DDRC		// Data Direction Register for Command Port

#define LCD_DATA_IN			PINB		// Data Input Register
#define LCD_DATA_OUT		PORTB		// Data Output Register
#define LCD_DATA_DIR		DDRB		// Data Direction Register for Data Port

// Command Port Bits
#define D_I					0x00		// D/I Bit Number
#define R_W					0x01		// R/W Bit Number
#define EN					0x02		// EN Bit Number
#define CSEL1				0x03		// CS1 Bit Number
#define CSEL2				0x04		// CS2 Bit Number

// Chips
#define CHIP1				0x00
#define CHIP2				0x01

// Commands
#define LCD_ON				0x3F
#define LCD_OFF				0x3E
#define LCD_SET_ADD			0x40
#define LCD_SET_PAGE		0xB8
#define LCD_DISP_START		0xC0

// Colors
#define BLACK				0xFF
#define WHITE				0x00

// Font Indices
#define FONT_LENGTH			0
#define FONT_FIXED_WIDTH	2
#define FONT_HEIGHT			3
#define FONT_FIRST_CHAR		4
#define FONT_CHAR_COUNT		5
#define FONT_WIDTH_TABLE	6

// Uncomment for slow drawing
// #define DEBUG

typedef struct {
	uint8_t x;
	uint8_t y;
	uint8_t page;
} lcdCoord;

typedef uint8_t (*ks0108FontCallback)(const uint8_t*);


static uint8_t  my_raster_screen[]  PROGMEM ={
255,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1
,1,1,1,3,1,1,1,1,1,1,1,1,1,3,1,1
,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1
,1,171,1,1,1,1,1,1,1,1,1,3,1,1,1,1
,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,3
,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1
,1,1,1,1,255,0,0,240,248,140,140,248,240,0,0,252
,252,0,0,252,252,0,0,4,252,252,68,196,252,56,0,0
,255,8,0,0,0,0,0,0,0,8,0,0,0,0,0,0
,0,0,0,8,0,0,0,0,0,0,0,0,0,8,0,0
,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0
,8,170,8,0,0,0,0,0,0,0,0,8,0,0,0,0
,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,8
,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0
,0,0,0,8,255,0,0,199,39,32,192,7,7,0,0,1
,3,6,6,3,1,0,0,4,7,7,0,0,7,7,0,0
,255,32,0,0,0,0,0,0,0,32,0,0,0,0,0,0
,0,0,0,32,0,0,0,0,0,0,0,0,0,32,0,0
,0,0,0,0,0,0,0,32,0,0,0,0,0,0,0,0
,32,170,32,0,0,0,0,0,0,0,0,32,0,0,0,0
,0,0,0,0,0,32,0,0,0,0,0,0,0,0,0,32
,0,0,0,0,0,0,0,0,0,32,0,0,0,0,0,0
,0,0,0,32,255,0,0,25,34,34,28,0,30,33,33,33
,0,30,33,33,30,0,255,33,33,30,0,30,41,41,46,0
,255,128,0,128,0,128,0,128,0,192,0,128,0,128,0,128
,0,128,0,192,0,128,0,128,0,128,0,128,0,192,0,128
,0,128,0,128,0,128,0,192,0,128,0,128,0,128,0,128
,0,170,0,128,0,128,0,128,0,128,0,192,0,128,0,128
,0,128,0,128,0,192,0,128,0,128,0,128,0,128,0,192
,0,128,0,128,0,128,0,128,0,192,0,128,0,128,0,128
,0,128,0,128,255,0,40,32,40,32,40,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,255,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0
,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0
,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0
,0,170,0,0,0,0,0,0,0,0,0,1,0,0,0,0
,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1
,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0
,0,0,0,0,255,0,16,8,16,32,16,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,255,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0
,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,0
,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0
,2,170,2,0,0,0,0,0,0,0,0,2,0,0,0,0
,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2
,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0
,0,0,0,2,255,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,255,8,0,0,0,0,0,0,0,8,0,0,0,0,0,0
,0,0,0,8,0,0,0,0,0,0,0,0,0,8,0,0
,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0
,8,170,8,0,0,0,0,0,0,0,0,8,0,0,0,0
,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,8
,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0
,0,0,0,8,255,0,0,124,20,4,0,124,20,104,0,124
,84,68,0,56,68,68,120,0,0,0,0,0,0,0,0,0
,255,128,128,128,128,128,128,128,128,160,128,128,128,128,128,128
,128,128,128,160,128,128,128,128,128,128,128,128,128,160,128,128
,128,128,128,128,128,128,128,160,128,128,128,128,128,128,128,128
,128,170,128,128,128,128,128,128,128,128,128,160,128,128,128,128
,128,128,128,128,128,160,128,128,128,128,128,128,128,128,128,160
,128,128,128,128,128,128,128,128,128,160,128,128,128,128,128,128
,128,128,128,128,255,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,124,16,124,0,72,104,88,0,0
};


//
// Function Prototypes
//

// Graphic Functions
void ks0108DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);
void ks0108DrawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);
void ks0108DrawRoundRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t radius, uint8_t color);
void ks0108FillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);
void ks0108InvertRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void ks0108SetInverted(uint8_t invert);
void ks0108SetDot(uint8_t x, uint8_t y, uint8_t color);

#define ks0108DrawVertLine(x, y, length, color) {ks0108FillRect(x, y, 0, length, color);}
#define ks0108DrawHoriLine(x, y, length, color) {ks0108FillRect(x, y, length, 0, color);}
#define ks0108DrawCircle(xCenter, yCenter, radius, color) {ks0108DrawRoundRect(xCenter-radius, yCenter-radius, 2*radius, 2*radius, radius, color);}
#define ks0108ClearScreen() {ks0108FillRect(0, 0, 127, 63, WHITE);}

// Font Functions
uint8_t ks0108ReadFontData(const uint8_t* ptr);		//Standard Read Callback
void ks0108SelectFont(const char* font, ks0108FontCallback callback, uint8_t color);
int ks0108PutChar(char c);
void ks0108Puts(char* str);
void ks0108Puts_P(PGM_P str);
uint8_t ks0108CharWidth(char c);
uint16_t ks0108StringWidth(char* str);
uint16_t ks0108StringWidth_P(PGM_P str);

// Control Functions
void ks0108GotoXY(uint8_t x, uint8_t y);
void ks0108Init(uint8_t invert);
inline uint8_t ks0108ReadData(void);
void ks0108WriteCommand(uint8_t cmd, uint8_t chip);
void ks0108WriteData(uint8_t data);

#endif
