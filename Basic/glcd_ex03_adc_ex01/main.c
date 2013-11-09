#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ks0108.h"
#include "arial_bold_14.h"
#include "corsiva_12.h"
#include "ADC.h"

void Welcome_Screen();
void createRaster2 (void);

uint16_t adc_result =0,pre_adc_result=0;
unsigned char Buffer[4]={0};







int main(void) {




// Initialize the LCD
	ks0108Init(0);
    ADC_init();

	_delay_ms(10);
    Welcome_Screen();

    _delay_ms(1000);

    ks0108ClearScreen();
    _delay_loop_1(100);

    ks0108GotoXY(80,15);
    ks0108Puts_P(PSTR("H_Rate:"));




    //ks0108Puts_P(PSTR("000"));


    ks0108GotoXY(80,37);
    ks0108Puts_P(PSTR("BP:"));

    ks0108GotoXY(100,47);
    ks0108Puts_P(PSTR("000"));

    // Select a font
	ks0108SelectFont(Arial_Bold_14, ks0108ReadFontData, BLACK);
    ks0108GotoXY(1,1);
    ks0108Puts_P(PSTR("Patient # 1"));

    ks0108DrawRect(1,15,70,45,BLACK);


     ks0108GotoXY(2,34);
    ks0108Puts_P(PSTR("Patient # 1"));

    _delay_ms(1000);
    ks0108FillRect(1,15,70,45,WHITE);
    ks0108DrawRect(1,15,70,45,BLACK);



	while(1)
        {

            adc_result = adc_read_2(0);
            if(pre_adc_result!=adc_result)
            {
                hex2Ascii(adc_result,Buffer);
            ks0108FillRect(90,25,30,10,WHITE);
             ks0108GotoXY(90,25);
            ks0108PutChar(Buffer[3]);
            ks0108PutChar(Buffer[2]);
            ks0108PutChar(Buffer[1]);
            ks0108PutChar(Buffer[0]);
            _delay_ms(100);
            pre_adc_result = adc_result;
            }



        }
}



//================================================

void Welcome_Screen(){



	// Select a font
	ks0108SelectFont(Arial_Bold_14, ks0108ReadFontData, BLACK);
	// Set a position
	ks0108GotoXY(15,10);
	// Print some text
	ks0108Puts_P(PSTR("Medical Lab"));
	// a nice little round rect
	ks0108DrawRoundRect(5, 5, 117, 20, 8, BLACK);

	// Once again :)
	// Select a font
	ks0108SelectFont(Corsiva_12, ks0108ReadFontData, BLACK);
	// Set a position
	ks0108GotoXY(5,30);
	// Print some text
	ks0108Puts_P(PSTR("Heart Rate, ECG Wave \n     and Blood Pressure \n        Measurement Unit"));




}

//==========================================================


void createRaster2 (void)
{
	unsigned int i;
	const char *data = my_raster_screen;
	int column = 0;
	int line =0;

	ks0108GotoXY(line,column);

	for (i = 0; i<1024; i++)
    {
        ks0108WriteData(pgm_read_byte(data++));
        _delay_us(100);
    }


}




//===========================
