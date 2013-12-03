/*

usart test file on atmega8 with 4800kbps baud rate
1MHz CRYSTAL is used
 */

#include <avr/io.h>
#include <util/delay.h>
#include "Usart.h"



int main(void)
{
    DDRB=0xFF;
   Usart_init();
   _delay_ms(100);
    Usart_printf("Hello Usart at 4800 with 1Mhz Crystal\r\n");


    while(1)
    {
    uint8_t temp = Usart_getch();
    Usart_putch('[');
    Usart_putch(temp);
    Usart_putch(']');
    Usart_putch(',');
    PORTB |= (1<<PB5);
        _delay_ms(1000);
        PORTB &= ~(1<<PB5);
        _delay_ms(1000);

    }

    return 0;
}
