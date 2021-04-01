#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char time_10ms = 0, time_100ms = 0, time_1s = 0, time_10s = 0;
char time_STOP = 0;
unsigned char FND_TBL[] = {0x3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7C,
							0X07, 0X7F, 0X67, 0X77, 0X7C, 0X39, 0X5E, 0X79, 0X71, 0X08, 0X80};

SIGNAL(SIG_INTERRUPT0){ // stop/resume
	cli();
	if(time_STOP == 0) time_STOP = 1;
	else time_STOP = 0;
	sei();
}
SIGNAL(SIG_INTERRUPT2){//reset
	cli();
	time_10ms = 0;
	time_100ms = 0;
	time_1s = 0;
	time_10s = 0;
	sei();
}

int main(void){
	DDRD = 0xFC;
	DDRG = 0x0F;
	DDRE = 0xFF;

	EICRA = 0x0F;
	EICRB = 0x00;
	
	EIMSK = 0x03;

	EIFR = 0x03;

	sei();

	while(1){
		PORTG = 0x07;
		PORTE = FND_TBL[time_10ms];

		_delay_ms(2);
		PORTG = 0x0B; 
		PORTE = FND_TBL[time_100ms]; 
		_delay_ms(2);
		PORTG = 0x0D; 
		PORTE = FND_TBL[time_1s]|0x80; 
		_delay_ms(3);
		PORTG = 0x0E; 
		PORTE = FND_TBL[time_10s]; 
		_delay_ms(3);
		if(time_STOP == 1) continue;
		
		time_10ms++;
		if(time_10ms == 10){
			time_10ms = 0;
			time_100ms++ ;
		}
		if(time_100ms == 10){
			time_100ms = 0;
			time_1s++ ;
		}
		if(time_1s == 10){
			time_1s = 0;
			time_10s++ ;
		}
		if(time_10s == 10){
			time_10s = 0;
		}
	}
	return 0;
}
