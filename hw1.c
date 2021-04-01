#include <avr/io.h>

int main(void){
	DDRA = 0xFF;
	PORTA = 0xFE;//11111110

	return 0;
}
