/*
 * BlinkLED.c
 *
 * Created: 30/05/2014 11:53:17 PM
 *  Author: Martin
 *  Edited by: Shavi Nachman
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void inithardware()
{
	//portA
	//DDRA = 0xFF;
	DDRB = (1 <<5); //use (1<<PORTx)
}

int main(void)
{
	
	inithardware(); //where is this file?
	
	while(1)
	{
		
		//PORTA = 0xFF;
		PORTB = (1<<5);
		_delay_ms(100);
		//PORTA = 0x00;
		PORTB = (0<<5);
		_delay_ms(500);
		
	}
}

