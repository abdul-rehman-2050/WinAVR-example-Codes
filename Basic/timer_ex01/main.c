/*
 TIMER0 TO OVERFLOW EVERY 50us
 CRYSTAL IS 8MHz
 PRESCALER is 1:8
TCNT0=206;    AS 256-50us = 206

TCCR0= 0x02; AS NORMAL MODE TIMER ZERO WITH PRESCALE 1:8

 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


ISR (TIMER0_OVF_vect){

TCNT0=206;

PORTB ^= (1<<2);



}



int main(void)
{
    //PORTD AS INPUT PORT
  DDRD=0;
  PORTD =255;

    //PORTB OUTPUT
    DDRB=255;
    PORTB=255;

  TCNT0=206;
  TCCR0=0x02;

  TIMSK |= (1<<TOIE0);      //TIMER0 OVERFLOW INTERRUPT
  sei();

    while(1)
    {

    }

    return 0;
}
