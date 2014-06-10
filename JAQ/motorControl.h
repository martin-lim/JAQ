/*
 * motorControl.h
 *
 * Created: 01/06/2014 10:33:26 PM
 *  Author: Shavi
 *  Edit: Martin
 */ 

#ifndef _MOTOR_CONTROL_H_
	#define _MOTOR_CONTROL_H_
	
	void motorStartUpSequence (void);
	
	void motorStop();
	
	void _motor1(uint16_t freq);
	
	void _motor2(uint16_t freq);
	
	void _motor3(uint16_t freq);
	
	void _motor4(uint16_t freq);
	
#endif
