#include <avr/io.h>

void delay(unsigned long x){
	while(x--);
}

unsigned char key_scan(void){
	unsigned char scan = 0;
	unsigned char input_data = 0;
	unsigned char key_control = 0;
	unsigned char key = 0;

	key_control = 0x10;

	for(scan = 1; scan <= 4; scan++){
		PORTE &= 0x0F;
		PORTE |= key_control;
		delay(1);
		input_data = PINF & 0x07;

		if(input_data != 0)
			key = scan;
		
		key_control <<= 1;
	}

	return key;
}

int main(void){
	unsigned char led = 0;
	unsigned char key = 0;
	DDRF = 0x00;
	DDRE = 0xFF;
	DDRA = 0xFF;

	while(1){
		key = key_scan();
		
		if(key == 1) led = 0x03;
		else if(key == 2) led = 0x0C;
		else if(key == 3) led = 0x30;
		else if(key == 4) led = 0xC0;
		else if(key == 0) led = 0xAA;

		PORTA = led;    
	}
}
