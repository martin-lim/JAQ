/*--------------------------
File Name	: PWM.c
Created by	: Martin Lim
Date 		: 05/03/2015

PWM library for ATMEGA2560

TODO: min max values of each function?
TODO: init counters first then assgin pins
TODO: use funtions to set init freq and dutyc
----------------------------*/

#define PRESCALER 64 //TODO: put this somewhere else

#include "PWM.h"
#include "config.h"

/************************************************
*			vTest	
************************************************/
void vTest()
{
	//for testing purposes only
	uint8_t u8Martin;		
	PORTB |= (1 << PB5);
	_delay_ms(500);
	PORTB &= ~(1 << PB5);
	_delay_ms(500);
}

/************************************************
*			vCounter1_Init
************************************************/
/* 16 bit Counter
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
*	- Counter Top Value = 0xFFFF
* OCR1A
* OCR1B
* OCR1C
************************************************/
void vCounter1_Init()
{
	/*Set Mode*/
	TCCR1B |= (1 << WGM13);
	TCCR1A |= ((1 << COM1A1) | (1 << COM1B1) | (1 << COM1C1));  //connect to pin
	/*Set Pin Data Direction*/
	DDRB |= ((1 << PB5) | (1 << PB6) | (1 << PB7));
	/*Set Clock Cycle*/
	TCCR1B |= ((1 << CS11) | (1 << CS10)); //FCPU/64
	/*Set Counter Top Value*/
	ICR1 = 0xFFFF;
	/*Set Counter Compare Value*/
	OCR1A = 0x0003; //smallest value
	OCR1B = 0x0003;
	OCR1C = 0x0003;
}

/************************************************
*			vCounter3_Init
************************************************/
/* 16 bit Counter
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
* ICR3
*	- Counter Top Value = 0xFFFF
* OCR3A
************************************************/
void vCounter3_Init()
{
	/*Set Mode*/
	TCCR3B |= (1 << WGM33);
	TCCR3A |= (1 << COM3A1);
	/*Set Pin Data Direction*/
	DDRE |= (1 << PE3);
	/*Set Clock Cycle*/
	TCCR3B |= (1 << CS31) | (1 << CS30);
	/*Set Counter Top Value*/
	ICR3 = 0xFFFF;
	/*Set Counter Compare Value*/
	OCR3A = 0x0003;
}

/************************************************
*			vPWM_Init
************************************************/
void vPWM_Init()
{
	vCounter1_Init();
	vCounter3_Init();
}

/************************************************
*			vPWM_SetFrequency
************************************************/
void vPWM_SetFrequency(float fpFrequency)
{
	uint16_t u16TopVal = F_CPU / (2 * PRESCALER * fpFrequency);
	ICR1 = u16TopVal;
	ICR3 = u16TopVal;
}

/************************************************
*			vPWM_SetDutyCycle
************************************************/
void vPWM_SetDutyCycle(uint8_t u8OutputNo, float fpDutyCycle)
{
	uint16_t u16CompareVal = (fpDutyCycle / 100) * 0xFFFF;

	if (u8OutputNo == 1)
	{
		OCR1A = u16CompareVal;
	}
	else if (u8OutputNo == 2)
	{
		OCR1B = u16CompareVal;
	}
	else if (u8OutputNo == 3)
	{
		OCR1C = u16CompareVal;
	}
	else if (u8OutputNo == 4)
	{
		OCR3A = u16CompareVal;
	}
}

/************************************************
*			vCounter1_DeInit
************************************************/
void vCounter1_DeInit()
{
	TCCR1A |= ((1 << COM1A1) | (1 << COM1B1) | (1 << COM1C1));
	//TODO: should this be here?
	//reverts pin opeartion from 'compare output mode' to normal GPIO 
	PORTB &= ~((1 << PB5) | (1 << PB6) | (1 << PB7)); //set output low
}

/************************************************
*			vCounter3_DeInit
************************************************/
void vCounter3_DeInit()
{
	TCCR3A |= (1 << COM3A1);
	PORTE &= ~(1 << PE3);
}

/************************************************
*			vPWM_DeInit
************************************************/
/*
* turns off all timers
************************************************/
void vPWM_DeInit()
{
	vCounter1_DeInit();
	vCounter3_DeInit();
}
