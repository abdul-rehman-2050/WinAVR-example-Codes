/*
 */

#include <avr/io.h>
#include <util/delay.h>
#include "Usart.h"
#include "ADC.h"





int main(void)
{
unsigned char Buffer[4]={0};


ADC_init ();
Usart_init();
_delay_ms(10);
Usart_printf("Hello_ADC\n\r");
_delay_ms(10);


    while(1)
   {
       int16_t adc_val= adc_read_2(0);
        hex2Ascii(adc_val,Buffer);
        Usart_printf("Channel_1=");
        Usart_putch(Buffer[3]);
        Usart_putch(Buffer[2]);
        Usart_putch(Buffer[1]);
        Usart_putch(Buffer[0]);
        Usart_putch('\n');
        Usart_putch('\r');
        _delay_ms(1000);

        Buffer[0]=0;
        Buffer[1]=0;
        Buffer[2]=0;
        Buffer[3]=0;
        adc_val=0;


        adc_val= adc_read_2(1);
        hex2Ascii(adc_val,Buffer);
        Usart_printf("Channel_2=");
        Usart_putch(Buffer[3]);
        Usart_putch(Buffer[2]);
        Usart_putch(Buffer[1]);
        Usart_putch(Buffer[0]);
        Usart_putch('\n');
        Usart_putch('\r');
        _delay_ms(1000);


   }

    return 0;
}


