#include <avr/io.h>

#define FND_C0 0x01
#define FND_C1 0x02
#define FND_C2 0x04
#define FND_C3 0x08

const char Font[17] = {0x3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D,
						0X7D, 0X07, 0X7F, 0X6F, 0X77, 0X7C,
						0X39, 0X5E, 0X79, 0X71, 0X00};

void delay(unsigned long x){
	while(x--);
}

void fnd_display(unsigned char digit0, unsigned char digit1, unsigned char digit2, unsigned char digit3){
	PORTG |= 0x0F;
	PORTG &= ~FND_C0;
	PORTB = Font[digit0];
	delay(100);

	PORTG |= 0x0F;
	PORTG &= ~FND_C1;
	PORTB = Font[digit1];
	delay(100);

	PORTG |= 0x0F;
	PORTG &= ~FND_C2;
	PORTB = Font[digit2];
	delay(100);

	PORTG |= 0x0F;
	PORTG &= ~FND_C3;
	PORTB = Font[digit3];
	delay(100);
}
	
int main(void){
	unsigned char digit0, digit1, digit2, digit3;
	int c_val;

	DDRB = 0xFF;
	DDRG = 0xFF;

	PORTB = 0x00;
	PORTG = 0xFF;

	TCCR1A = 0x00;
	TCCR1B = 0x07;
	TCCR1C = 0x00;

	while(1){
		c_val = TCNT1;
		
		digit0 = c_val / 1000;
		digit1 = (c_val % 1000) / 100;
		digit2 = ((c_val % 1000) % 100) / 10;
		digit3 = ((c_val % 1000) % 100) % 10;
		
		fnd_display(digit0, digit1, digit2, digit3);
	}
} 
