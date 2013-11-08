#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "ks0108.h"
#include "arial_bold_14.h"
#include "corsiva_12.h"


void Welcome_Screen();



int main(void) {


// Initialize the LCD
	ks0108Init(0);
	_delay_ms(10);
    Welcome_Screen();



	while(1);
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
