/*
 * motorControl.h
 *
 * Created: 01/06/2014 10:33:26 PM
 *  Author: Shavi
 *  Edit: Martin
 */ 

#ifndef _MOTOR_CONTROL_H_
#define _MOTOR_CONTROL_H_

#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__
#endif

#define MOTOR1 1
#define MOTOR2 2
#define MOTOR3 3
#define MOTOR4 4
#define TIMER_TOP_VAL 0xFFFF //65535

#include <avr/io.h>

/**********************************************************
*			Function Declaration
**********************************************************/
void Timer1_init(void);			//TODO: rdy 2b tested (safety)
void Timer3_init(void);			//TODO: rdy 2b tested
void Motor_arm(void);		//TODO: rdy 2b tested
void Motor_disarm(void);	//TODO: rdy 2b tested
void Motor_drive(int Motor_number, uint16_t pwm_duty);

#endif
