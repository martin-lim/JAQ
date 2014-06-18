/*
 * JAQ.c
 *
 * Created: 1/06/2014 10:26:00 PM
 *  Author: Shavi
 *  Edit: Martin
 */ 


#include "jaq.h"

int main(void)
{
	init_IO();
	init_timers();

	//for testing only
	OCR0A = 251;
	OCR0B = 10;

	while(1)
	{
		//blink led
		PORTB |= (1 << PB5);

		//updateSensors;
		//updateStabilise;
		//MotorControl;
    }
}