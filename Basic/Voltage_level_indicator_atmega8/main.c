/*
 */

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include "ADC.h"


#define  output_1  PD2
#define  output_2  PD3
#define  output_3  PD4
#define  output_4  PD5
#define  output_5  PD6
#define  output_6  PD7
#define  output_7  PB0
#define  output_8  PB1
#define  output_9  PB2
#define  output_10 PB3


#define  CLEAR_out_1  ((PORTD)&=~(1<<output_1))
#define  CLEAR_out_2  ((PORTD)&=~(1<<output_2))
#define  CLEAR_out_3  ((PORTD)&=~(1<<output_3))
#define  CLEAR_out_4  ((PORTD)&=~(1<<output_4))
#define  CLEAR_out_5  ((PORTD)&=~(1<<output_5))
#define  CLEAR_out_6  ((PORTD)&=~(1<<output_6))
#define  CLEAR_out_7  ((PORTB)&=~(1<<output_7))
#define  CLEAR_out_8  ((PORTB)&=~(1<<output_8))
#define  CLEAR_out_9  ((PORTB)&=~(1<<output_9))
#define  CLEAR_out_10  ((PORTB)&=~(1<<output_10))


#define SET_out_1    ((PORTD)|=(1<<(output_1)))
#define SET_out_2    ((PORTD)|=(1<<(output_2)))
#define SET_out_3    ((PORTD)|=(1<<(output_3)))
#define SET_out_4    ((PORTD)|=(1<<(output_4)))
#define SET_out_5    ((PORTD)|=(1<<(output_5)))
#define SET_out_6    ((PORTD)|=(1<<(output_6)))
#define SET_out_7    ((PORTB)|=(1<<(output_7)))
#define SET_out_8    ((PORTB)|=(1<<(output_8)))
#define SET_out_9    ((PORTB)|=(1<<(output_9)))
#define SET_out_10    ((PORTB)|=(1<<(output_10)))






int main(void)
{
    uint16_t temp =0,adc_result=0;
    uint8_t adc_val1=0,adc_val2=0,adc_val3=0;
 DDRB = 0xFF;       // Make PORTB an Output Port
 PORTB = 0x00;      //CLEAR ALL PINS OF PORTB

 DDRD = 0xFF;
 PORTD= 0x00;

 DDRC = 0x00;       //MAKE ADC CHANNEL PINS AS INPUT
 PORTC = 0x00;

ADC_init();

    while(1)
    {

        adc_result = adc_read(0);
        temp = adc_result*10;
        temp /=1023;
        adc_val1=temp;

        _delay_ms(100);

        adc_result = adc_read(0);
        temp = adc_result*10;
        temp /=1023;
        adc_val2=temp;

        _delay_ms(100);

        adc_result = adc_read(0);
        temp = adc_result*10;
        temp /=1023;
        adc_val3=temp;

        _delay_ms(100);


        temp = (adc_val1+adc_val2+adc_val3)/3;


        if(temp>9)
        {
            PORTB=0xFF;  //SET ALL BITS HIGH
            PORTD=0xFF;  //ALSO SET ALL BITS ON PORTD
        }
        else if(temp>8)
        {
            PORTB=0xFF;  //SET ALL BITS HIGH
            PORTD=0xFF;  //ALSO SET ALL BITS ON PORTD
            CLEAR_out_10;
        }
        else if(temp>7)
        {
            PORTB=0xFF;  //SET ALL BITS HIGH
            PORTD=0xFF;  //ALSO SET ALL BITS ON PORTD
            CLEAR_out_10;
            CLEAR_out_9;
        }
        else if(temp>6)
        {
            PORTB=0xFF;  //SET ALL BITS HIGH
            PORTD=0xFF;  //ALSO SET ALL BITS ON PORTD
            CLEAR_out_10;
            CLEAR_out_9;
            CLEAR_out_8;
        }
        else if(temp>5)
        {
            PORTB=0x00;  //clear ALL BITS HIGH
            PORTD=0xFF;  //ALSO SET ALL BITS ON PORTD
        }
        else if(temp>4)
        {
            PORTB=0x00;
            PORTD=0xFF;
            CLEAR_out_6;
        }
        else if(temp>3)
        {
            PORTB=0x00;  //SET ALL BITS HIGH
            PORTD=0xFF;  //ALSO SET ALL BITS ON PORTD
            CLEAR_out_6;
            CLEAR_out_5;
        }
        else if(temp>2)
        {
            PORTB=0x00;  //CLEAR ALL BITS HIGH
            PORTD=0x00;  //ALSO CLEAR ALL BITS ON PORTD
            SET_out_1;
            SET_out_2;
            SET_out_3;
        }
        else if(temp>1)
        {
            PORTB=0x00;  //CLEAR ALL BITS HIGH
            PORTD=0x00;  //ALSO CLEAR ALL BITS ON PORTD
            SET_out_1;
            SET_out_2;
        }
        else if(temp>0)
        {
            PORTB=0x00;  //CLEAR ALL BITS HIGH
            PORTD=0x00;  //ALSO CLEAR ALL BITS ON PORTD
            SET_out_1;
        }
        else{
            PORTB=0x00;  //SET ALL BITS HIGH
            PORTD=0x00;  //ALSO SET ALL BITS ON PORTD
        }




    }

    return 0;
}
