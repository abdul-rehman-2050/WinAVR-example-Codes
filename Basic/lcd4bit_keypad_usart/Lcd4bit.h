#include <avr/io.h>




#define LCD_PORT PORTC
#define LCD_DDR  DDRC
#define RS PC2
#define EN PC3

#define LCD_CURSOR_OFF	0x0C
#define	LCD_CLEAR		0x01

#define	LINE_1			0x80
#define	LINE_2			0xC0
#define	LINE_3			0x94
#define	LINE_4			0x0D4
#define Delay_ms        _delay_ms


#define	SHIFT_CURSOR_RIGHT	0x06

void Lcd_init_4bit();
void Lcd_Cmd(unsigned char);
void Lcd_Chr_CP(unsigned char);
void strob();
void lcd_nibble(unsigned char);
void Lcd_Puts(const char*);




//======================================================
void Lcd_init_4bit()
{

LCD_DDR=255;    // MAKE DATA DIRECTION REGISTER OUTPUT

LCD_PORT  &= ~( 1 << RS );  //CLEAR RS
LCD_PORT  &= ~( 1 << EN );  //CLEAR EN

Delay_ms(250);
lcd_nibble(40);
Lcd_Cmd(40);		//init. LCD 2 lines, 5x7 matrix
Lcd_Cmd(12);
Lcd_Cmd(0x0F);		//disp on cursor on, Blink
Delay_ms(250);

}

void strob()
{
	LCD_PORT  |= ( 1 << EN );  //SET EN
	Delay_ms(1);
	LCD_PORT  &= ~( 1 << EN );  //CLEAR EN
}

//======================================================================

void Lcd_Cmd(unsigned char value)
{

	LCD_PORT  &= ~( 1 << RS );  //CLEAR RS
	lcd_nibble(value);
	LCD_PORT = (LCD_PORT & 0x0F) | (value << 4);
	strob();
	Delay_ms(15)    ;

}

//======================================================================

void Lcd_Chr_CP(unsigned char value)
{
	LCD_PORT  |= ( 1 << RS );  //SET RS
	lcd_nibble(value);
	value = (value & 0x0F) |  (value << 4);
	lcd_nibble(value);
	Delay_ms(15);


}

//========================================================================
void lcd_nibble(unsigned char c)
{

LCD_PORT = (LCD_PORT & 0x0F) | (c & 0xF0); //in higher nibble 4-7
strob();

}

void Lcd_Puts(const char* str)
{
	while(*str)
			{
				Lcd_Chr_CP(*(str++));

			}


}
//==================================================================


