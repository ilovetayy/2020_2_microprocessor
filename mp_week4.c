#include <avr/io.h>

const char Font[17] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,
						0x7D,0x07,0x7F,0x6F,0x77,0x7C,
						0x39,0x5E,0x79,0x71,0x00};

void delay(unsigned long x){
	while(x--);
}

int main(void){
	unsigned int count = 1;	
	unsigned int digit0, digit1, digit2;

	DDRB = 0xFF;
	DDRG = 0xFF;

	PORTB = 0x00;
	PORTG = 0xFF;

	digit0 = 1;
	digit1 = 1;
	digit2 = 1;
	
	PORTG |= 0x0F;
	PORTG &= 0b11110111;//C3
	PORTB = Font[0];
	delay(10000);

	while(count <= 999){
		PORTG |= 0x0F;
		PORTG &= 0b11110111;//C3
		PORTB = Font[digit0];
		digit0++;
		if(digit0 == 10) digit0 = 0;

		if(count < 10){
			delay(10000);
			count++;
			continue;
		}

		delay(100);

		digit1 = count / 10;
		if(digit1 >= 10) digit1 %= 10;

		PORTG |= 0x0F;
		PORTG &= 0b11111011;//C2
		PORTB = Font[digit1];

		if(count < 100){
			delay(10000);
			count++;
			continue;
		}

		delay(100);

		digit2 = count / 100;

		PORTG |= 0x0F;
		PORTG &= 0b11111101;//C1
		PORTB = Font[digit2];

		delay(10000);
		count++;
	}
	return 0;
}
