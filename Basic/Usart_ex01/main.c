/*
 IN THE NAME OF ALLAH THE MOST BENEFICENT THE MOST MERCIFUL


 October 20,2013
 AT 5:03PM


 hello world example of serial port;

 */

#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"


int main(void)
{

Usart_init();
_delay_ms(100);
Usart_printf("Hello Usart\r\n");
_delay_ms(1000);
    while(1)
        {
            unsigned char ch = Usart_getch();
            Usart_putch('[');
            Usart_putch(ch);
            Usart_putch(']');
            Usart_putch(',');

        }


    return 0;
}
