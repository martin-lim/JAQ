/*
 * BlinkLED.c
 *
 * Created: 30/05/2014 11:53:17 PM
 *  Author: Martin Lim
 *  Edited by: Shavi Nachman
 */ 

#include <avr/io.h>
#include <util/delay.h>

void inithardware() //TODO: move to init_IO
{

	DDRB |= (1<<PORTB5);
}

int BlinkLED(int waittime)
{
	for (int i=0;i<500000;i++)
	{
		PORTB |= (1<<PORTB5);
		_delay_ms(waittime);
		PORTB &= ~(1<<PORTB5);
		_delay_ms(waittime);
		
	}

}

