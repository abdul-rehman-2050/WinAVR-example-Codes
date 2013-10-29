//===============================================
#define KEYPAD B  //KEYPAD IS ATTACHED ON PORTB

#define KEYPAD_PORT PORTB
#define KEYPAD_DDR   DDRB
#define KEYPAD_PIN   PINB

//=================================================


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
               switch(r*3+c+48){
            case ';':
                return '1';
                break;

            case ':':
                return '2';
                break;

            case '9':
                return '3';
                break;

            case '8':
                return '4';
                break;

            case '7':
                return '5';
                break;

            case '5':
                return '7';
                break;

            case '4':
                return '8';
                break;

            case '3':
                return '9';
                break;

            case '1':
                return '0';
                break;

            case '2':
                return '*';
                break;

            default:
                return (r*3+c+48);






               }
            }
      }

    }

      return 0XFF;//Indicate No key pressed
}



