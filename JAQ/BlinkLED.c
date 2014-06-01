/*
 * BlinkLED.c
 *
 * Created: 30/05/2014 11:53:17 PM
 *  Author: Martin
 *  Edited by: Shavi Nachman
 */ 

#include <avr/io.h>
#include <util/delay.h>

void inithardware()
{
	//portA
	//DDRA = 0xFF;
	DDRB |= (1<<PB5);
}

int BlinkLED(int waittime)
{
	for (int i=0;i<500000;i++)
	{
		PORTB |= (1<<<<PB5);
		_delay_ms(waittime);
		PORTB &= ~(1<<<<PB5);
		_delay_ms(waittime);
		
	}

}

