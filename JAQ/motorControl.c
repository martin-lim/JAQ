/*
 * motorControl.c
 *
 * Created: 10/06/2014 06:06:00 PM
 *  Author: Martin Lim
 */ 

#include "motorControl.h"

/**********************************************************
*			Function Definitions
**********************************************************/

/************************************************
*			Motor_arm
************************************************/
void Motor_arm()
{
	Timer1_init();	//Motor1, Motor2, Motor3
	Timer3_init();	//Motor4
}

/************************************************
*			Timer1_init
*
* Waveform Generation Mode
*	- PWM, Phase and Frequency Correct
*	- TOP=ICRn, Update of OCRnx at = BOTTOM,
*	  TOV Flag Set on = BOTTOM
* Compare Output Mode
*	- Clear OC1A/OC1B/OC1C on Compare Match when up-counting
*	  Set OC1A/OC1B/OC1C on Compare Match when down-counting
* Pin Data Direction
*	- Make PB5, PB6, PB7 Output
* Clock Select 
*	- clk(I/O)/64 (From prescaler) 
* ICR1
*	- define in header file
* OCR1A
* OCR1B
* OCR1C
************************************************/
void Timer1_init()
{
	TCCR1B |= (1 << WGM13);
	TCCR1A |= ((1 << COM1A1) | (1 << COM1B1) | (1 << COM1C1));
	DDRB |= ((1 << PB5) | (1 << PB6) | (1 << PB7));
	TCCR1B |= ((1 << CS11) | (1 << CS10));
	ICR1 = TIMER_TOP_VAL;
	OCR1A = 10; //Period //TODO:?
	OCR1B = 10;
	OCR1C = 10;
}

/************************************************
*			Timer3_init
*
* Waveform Generation Mode
*	- PWM, Phase and Frequency Correct
*	- TOP=ICRn, Update of OCRnx at = BOTTOM,
*	  TOV Flag Set on = BOTTOM
* Compare Output Mode
*	- Clear OC3A on Compare Match when up-counting
*	  Set OC3A on Compare Match when down-counting
* Pin Data Direction
*	- Make PE3 Output
* Clock Select
*	- clk(I/O)/64 (From prescaler)
* ICR3 (define in header file)
* OCR3A
************************************************/
void Timer3_init()
{
	TCCR3B |= (1 << WGM33);
	TCCR3A |= (1 << COM3A1);
	DDRE |= (1 << PE3);
	TCCR3B |= (1 << CS31) | (1 << CS30);
	ICR3 = TIMER_TOP_VAL;//65535;
	OCR3A = 10; //PE3
}

/************************************************
*			Motor_disarm
*
* Revert Compare Output Mode to
*	- Normal port operation
* Make the Outputs Low
************************************************/
void Motor_disarm()
{
	//Timer1
	TCCR1A |= ((1 << COM1A1) | (1 << COM1B1) | (1 << COM1C1));
	PORTB &= ~((1 << PB5) | (1 << PB6) | (1 << PB7));
	//Timer3
	TCCR3A |= (1 << COM3A1);
	PORTE &= ~(1 << PE3);
}

/************************************************
*			Motor_drive
*
* Accepts a value from 0 to TIMER_TOP_VAL as duty cycle.
* If value is 0 or top value, timer will be turned off,
* and port will revert to normal operation.
*
* choose motor with Motor_number
************************************************/
void Motor_drive(int Motor_number, uint16_t pwm_duty)
{
	if (pwm_duty == 0)
	{
		//set pin low
		switch (Motor_number)
		{
			case MOTOR1:
				TCCR1A &= ~(1 << COM1A1);
				PORTB &= ~(1 << PB5);
				break;

			case MOTOR2:
				TCCR1A &= ~(1 << COM1B1);
				PORTB &= ~(1 << PB6);
				break;

			case MOTOR3:
				TCCR1A &= ~(1 << COM1C1);
				PORTB &= ~(1 << PB7);
				break;

			case MOTOR4:
				TCCR3A &= ~(1 << COM3A1);
				PORTE &= ~(1 << PE3);
				break;

			default:
				break;
		}
	}
	else if (pwm_duty == TIMER_TOP_VAL)
	{
		//set pin high
		switch (Motor_number)
		{
			case 1:
				TCCR1A &= ~(1 << COM1A1);
				PORTB |= (1 << PB5);
				break;

			case 2:
				TCCR1A &= ~(1 << COM1B1);
				PORTB |= (1 << PB6);
				break;

			case 3:
				TCCR1A &= ~(1 << COM1C1);
				PORTB |= (1 << PB7);
				break;

			case 4:
				TCCR3A &= ~(1 << COM3A1);
				PORTE |= (1 << PE3);
				break;

			default:
				break;
		}
	}
	else
	{
		//set pin to timer
		switch (Motor_number)
		{
			case 1:
				TCCR1A |= (1 << COM1A1);
				OCR1A = pwm_duty;
				break;

			case 2:
				TCCR1A |= (1 << COM1B1);
				OCR1B = pwm_duty;
				break;

			case 3:
				TCCR1A |= (1 << COM1C1);
				OCR1C = pwm_duty;
				break;

			case 4:
				TCCR3A |= (1 << COM3A1);
				OCR3C = pwm_duty;
				break;

			default:
				//error: motor not found
				break;
		}

	}
}