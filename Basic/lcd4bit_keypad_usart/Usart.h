
#ifndef F_CPU
 #define F_CPU			1000000
#endif // F_CPU

#define BAUD_RATE		4800



// AVR-GCC compiler compatibility
// avr-gcc compiler v3.1.x and older doesn't support outb() and inb()
//      if necessary, convert outb and inb to outp and inp
#ifndef outb
	#define outb(sfr,val)  (_SFR_BYTE(sfr) = (val))
#endif
#ifndef inb
	#define inb(sfr) _SFR_BYTE(sfr)
#endif

/* defines for future compatibility */
#ifndef cbi
	#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
	#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif




void Usart_init(){

/* initialize UART(s) depending on CPU defined */
  /* m8 */
  UBRRH = (((F_CPU/BAUD_RATE)/16)-1)>>8; 	// set baud rate
  UBRRL = (((F_CPU/BAUD_RATE)/16)-1);
  UCSRB = (1<<RXEN)|(1<<TXEN);  // enable Rx & Tx
  UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);  // config USART; 8N1

}


char Usart_getch(void)
{
  while(!(inb(UCSRA) & _BV(RXC))) ;
  return (inb(UDR));
}


void Usart_putch(char ch)
{
  /* m8 */
  while (!(inb(UCSRA) & _BV(UDRE)));
  outb(UDR,ch);
}


void Usart_printf(const char* str){
while(*str!=0){

    Usart_putch(*str);
    str++;

}
}
