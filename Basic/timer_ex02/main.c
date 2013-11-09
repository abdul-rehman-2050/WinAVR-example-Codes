/*
 one second delay with timer one
 with out interrupt;
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t freq1=0;



void T1Delay_oneSecond(){
    freq1=0;
    TCNT1H = 0x85;
    TCNT1L = 0xEE;

    TCCR1A = 0x00;  //NORMAL MODE
    TCCR1B = 0x04;  //NORMAL MODE WITH PRESCALE = 1:256

    while((TIFR&(1<<TOV1))==0){

        if((PIND&_BV(PD2))==0)
        {
            freq1++;
            while((PIND&_BV(PD2))==0);
        }

    }    //WAIT FOR TF1 TO ROLL

    TCCR1B = 0;
    TIFR = 1<<TOV1;     //CLEAR TOV1


}



int main(void)
{
    //PORTD AS INPUT PORT
  DDRD=0;
  PORTD =255;

    //PORTB OUTPUT
    DDRB=255;
    PORTB=255;

    DDRC = 255;
    PORTC = 255;



    while(1)
    {
        PORTB=freq1;

        T1Delay_oneSecond();

    }

    return 0;
}
