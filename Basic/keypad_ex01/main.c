/*
 IN THE NAME OF ALLAH THE MOST BENEFICENT THE MOST MERCIFUL


 4x4 KEYPAD INTERFACING WITH AVR
 */

#include <avr/io.h>
#include <util/delay.h>


//===============================================
#define KEYPAD B  //KEYPAD IS ATTACHED ON PORTB

#define KEYPAD_PORT PORTB
#define KEYPAD_DDR   DDRB
#define KEYPAD_PIN   PINB
//===============================================
uint8_t GetKeyPressed();
//==============================================
int main(void)
{
DDRD = 0xFF;
PORTD = 255;

uint8_t key;

    while(1)
    {
        key=GetKeyPressed();
        if(key<255)
            {
            PORTD = key;

            }

    }

    return 0;
}

//==================================================



uint8_t GetKeyPressed()
{
    uint8_t r,c;
    KEYPAD_PORT |= 0x0F;

    for(c=0;c<4;c++)
    {
      KEYPAD_DDR&=~(0X7F);
      KEYPAD_DDR|=(0X40>>c);
      for(r=0;r<4;r++)
      {
           if(!(KEYPAD_PIN & (0X08>>r)))
            {
               return (r*3+c);
            }
      }

    }

      return 0XFF;//Indicate No key pressed
}


