/*
 * motorControl.h
 *
 * Created: 01/06/2014 10:33:26 PM
 *  Author: Shavi
 */ 

#ifndef _MOTOR_CONTROL_H_
	#define _MOTOR_CONTROL_H_
	
	void motorStartUpSequence (void);
	
	void motorStop();
	
	void _motor1(uint16_t freq);
	
	void _motor2(uint16_t freq);
	
	void _motor3(uint16_t freq);
	
	void _motor4(uint16_t freq);
	
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
	
#endif