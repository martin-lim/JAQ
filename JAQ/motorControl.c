/*
 * motorControl.c
 *
 * Created: 10/06/2014 06:06:00 PM
 *  Author: Martin Lim
 */ 

#include "motorControl.h"
	
//confirm output pins, below
void _motor1 (uint16_t PWMfreq)
{
	//OCR4C = PWMfreq; 
}

void _motor2 (uint16_t PWMfreq)
{
	//OCR4B = PWMfreq;
}

void _motor3 (uint16_t PWMfreq)
{
	//OCR1A = PWMfreq;
}

void _motor4(uint16_t PWMfreq)
{
	//OCR1B = PWMfreq;
}
	
