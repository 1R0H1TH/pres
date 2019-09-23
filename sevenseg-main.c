//Prints a decimal number 
//on the display
#include <avr/io.h>
#include <util/delay.h>

const int portB[] = {1,1,0,0,0,0,0,1,0,0,0};
const int portD[] = {0b00000000,0b11100100,0b10010000,0b11000000,0b01100100,0b01001000,0b00001000,0b11100000,0b00000000,0b01000000,0b00011000};

void setnum(int num);

int main (void)
{
	
	
 //set PD2-PD7 as output pins 0xFC=0b11111100 (binary)
  DDRD   |= 0xFC;
  //set PB0 as output pin
  DDRB    |= ((1 << DDB0));
  int i=0;
  while (1) {
	setnum(i++);
	_delay_ms(1000);
	if (i >= 10) i=0;
  }

  /* . */
  return 0;

}

void setnum(int num){
	if (num < 0 || num > 10) num = 10;
	PORTB = ((portB[num] <<  PB0));
  PORTD = portD[num];
}
