/*
 IN THE NAME OF ALLAH THE MOST BENEFICIAL THE MOST MERCIFUL
 */

#include <avr/io.h>
#include <avr/delay.h>

int main (void) {

 DDRB = 0xFF;       // Make PORTB an Output Port
 PORTB = 0xFF;      //SET ALL PINS OF PORTB

while(1)
        {
          PORTB  &= ~( 1 << PB0 );  //CLEAR PORTB PIN0
            _delay_ms(1000);
          PORTB |= ( 1 << PB0 );
          _delay_ms(1000);

        }

    return 0;
}
