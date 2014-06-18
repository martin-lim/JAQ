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
	//TODO: if pwmfreq is zero, exclude it from OCR4C
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
	
void motorStartUpSequence(void)
{

}

void motorStop(void)
{

}
