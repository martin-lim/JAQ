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
	init_timers;

	while(1)
	{
		OCR0A = 250;
		OCR0B = 240;
		//updateSensors;
		//updateStabilise;
		//MotorControl;
    }
}