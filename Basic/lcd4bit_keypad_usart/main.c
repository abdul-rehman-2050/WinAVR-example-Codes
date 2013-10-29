
/*

IN THE NAME OF ALLAH THE MOST BENEFICENT THE MSOT MERCIFUL


20-OCT-2013
START_TIME: 6:43AM
LOCK_COMPLETED_AT: 7:15AM

ADC_START_TIME: 5:48 ON 21-OCT-2013
ADC_COMPLETED: 6:10AM ON 21-OCT-2013
BUG_FIXING_START AT: 6:11AM ON 21-OCT-2013
BUG_FIXING_COMPLETE AT: 6:52AM ON 21-OCT-2013

*/
#include <avr/io.h>
#include <util/delay.h>
#include "Keypad.h"
#include "Lcd4bit.h"
#include "Usart.h"



void UnLock_S_Scope();
unsigned char digit1=0,digit2=0,digit3=0,digit4=0;
void bcd4int(uint16_t value)
{

digit1=(value%10)+48;
digit2=((value/10)%10)+48;
digit3=((value/100)%10)+48;
digit4=((value/1000)%10)+48;

}


void adc_init(){

ADCSRA = _BV(ADEN) | _BV(ADPS2); //ENABLE ADC WITH PRESCALER 16
ADMUX = 0xC0; // 2.5V VREF, ADC0 SIGNEL ENDED INPUT, DATA WILL BE RIGHT JUSTIFIED

}

uint16_t read_adc0()
{
uint8_t LOW_ADC_VAL =0;
uint16_t the_result = 0;
ADCSRA |= (1<<ADSC);        //START CONVERSION
while((ADCSRA&(1<<ADIF))==0);       //WAIT FOR CONVERSION TO COMPLETE

LOW_ADC_VAL = ADCL;
the_result = ADCH<<8 | LOW_ADC_VAL;
return the_result;
}




int main(void)
{

Usart_init();
_delay_ms(100);
Lcd_init_4bit();
_delay_ms(100);
adc_init();
Lcd_Puts("Electronic ");
Lcd_Cmd(LINE_2+3);
Lcd_Puts("Stethoscope");
_delay_ms(2000);

Lcd_Cmd(LCD_CLEAR);


UnLock_S_Scope();

    while(1)
    {
        uint16_t adc_val = 0;
        unsigned char key = GetKeyPressed();

        if(key=='*'){
            Usart_printf("Scope is Locked\r\n");
            UnLock_S_Scope();

        }
       /* if((key!=pre_key)&&((key>47&&key<58)|(key=='*')))
        {
            Lcd_Chr_CP(key);
            pre_key=key;
        }
        */


        adc_val = read_adc0();
        bcd4int(adc_val);
        Lcd_Cmd(LINE_2+2);
        Lcd_Chr_CP(digit4);
        Lcd_Chr_CP(digit3);
        Lcd_Chr_CP(digit2);
        Lcd_Chr_CP(digit1);
        Usart_putch(digit4);
        Usart_putch(digit3);
        Usart_putch(digit2);
        Usart_putch(digit1);
        Usart_putch(10);
        Usart_putch(13);

        _delay_ms(50);



    }

    return 0;
}

//====================================================

void UnLock_S_Scope()
{
    unsigned char password_flag=0;

        Lcd_Cmd(LCD_CLEAR);
        Lcd_Puts("Enter Password..");
        Lcd_Cmd(LINE_2+2);


    while(password_flag==0){

    unsigned char key1=0,key2=0,key3=0,key4=0;
    while(key1<'0'||key1>'9'){key1=GetKeyPressed();}
    Lcd_Chr_CP('*');

    _delay_ms(100);
    do{key2=GetKeyPressed();}while(key2==key1);

    while(key2<'0'||key2>'9'){key2=GetKeyPressed();}
    Lcd_Chr_CP('*');

    _delay_ms(100);
    do{key3=GetKeyPressed();}while(key3==key2);


    while(key3<'0'||key3>'9'){key3=GetKeyPressed();}
    Lcd_Chr_CP('*');

    _delay_ms(100);
    do{key4=GetKeyPressed();}while(key4==key3);


    while(key4<'0'||key4>'9'){key4=GetKeyPressed();}
    Lcd_Chr_CP('*');


    if(key1=='1'&&key2=='2'&&key3=='4'&&key4=='5')
    {
    password_flag = 1;
    }
    else {

        Lcd_Cmd(LCD_CLEAR);
        Lcd_Puts("Wrong Password...");
        _delay_ms(1000);
        Lcd_Cmd(LCD_CLEAR);
        Lcd_Puts("Enter Password..");
        Lcd_Cmd(LINE_2+2);


    }
}

Lcd_Cmd(LCD_CLEAR);
Lcd_Puts("Unlocked...");
Usart_printf("Stethoscope is  Unlocked Successfully\r\n");
_delay_ms(2000);
Lcd_Cmd(LCD_CLEAR);

Lcd_Puts("Processing...");
Lcd_Cmd(LINE_2+2);


}

