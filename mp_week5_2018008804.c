#include <avr/io.h>

int power(int x, int y){
	if(y == 0) return 1;
	else return x * power(x, y - 1);
}
int main(void){
	unsigned char input_data;
	DDRA = 0x00;
	DDRB = 0xFF;

	while(1){
		input_data = PINA & 0x0F;
		if(input_data > 7) PORTB = 0x00;
		else PORTB = power(2, input_data);
	}
}
