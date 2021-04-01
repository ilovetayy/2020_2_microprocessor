#include <avr/io.h>
#include <avr/interrupt.h>

#define FND_C0 0x01
#define FND_C1 0x02
#define FND_C2 0x04
#define FND_C3 0x08

const char Font[17] = {0x3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D,
						0X7D, 0X07, 0X7F, 0X6F, 0X77, 0X7C,
						0X39, 0X5E, 0X79, 0X71, 0X00};

unsigned char digit0 = 0;
unsigned char digit1 = 0;
unsigned char digit2 = 0;
unsigned char digit3 = 0;

int j = -1;

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

SIGNAL(SIG_INTERRUPT0){
	 j = 0000;
	 delay(3000);
}
SIGNAL(SIG_INTERRUPT1){
	 j = 1111;
	 delay(3000);
}
SIGNAL(SIG_INTERRUPT2){
	 j = 2222;
	 delay(3000);
}
SIGNAL(SIG_INTERRUPT3){
	 j = 3333;
	 delay(3000);
}
SIGNAL(SIG_INTERRUPT4){
	 j = 4444;
	 delay(3000);
}
SIGNAL(SIG_INTERRUPT5){
	 j = 5555;
	 delay(3000);
}
SIGNAL(SIG_INTERRUPT6){
	 j = 6666;
	 delay(3000);
}
SIGNAL(SIG_INTERRUPT7){
	 j = 7777;
	 delay(3000);
}

int main(void){
	DDRB = 0xFF;
	DDRG = 0xFF;

	PORTB = 0x00;
	PORTG = 0xFF;

	EIMSK = 0xFF;

	EICRA = 0xFF;
	EICRB = 0xFF;

	sei();

	int i = 0;

	while(1){
		if(j != -1){
			digit0 = j / 1000;
			digit1 = (j % 1000) / 100;
			digit2 = ((j % 1000) % 100) / 10;
			digit3 = ((j % 1000) % 100) % 10;
		
			fnd_display(digit0, digit1, digit2, digit3);

			j = -1;
		}
		else{
			digit0 = i / 1000;
			digit1 = (i % 1000) / 100;
			digit2 = ((i % 1000) % 100) / 10;
			digit3 = ((i % 1000) % 100) % 10;
		
			fnd_display(digit0, digit1, digit2, digit3);

			i++;
			if(i == 10000) i = 0;
		}
	}
}
