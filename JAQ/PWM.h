/*--------------------------
File Name	: PWM.h
Created by	: Martin Lim
Date 		: 05/03/2015

PWM library for ATMEGA2560
----------------------------*/

#ifndef _PWM_H_
#define _PWM_H_

/************************************************
*			vPWM_Init
************************************************/
/* Initialization for PWM generation
*   - Initialize Counters 1 and 3
*   - Sets PWM Frequency to around 1.9Hz
*   - Sets Duty Cycle to around 0.001%
************************************************/
void vPWM_Init();

/************************************************
*			vPWM_DeInit
************************************************/
/* Deinitialization for PWM generation
*   - Reverts pin mode back to GPIO
*   - All Outputs Low
************************************************/
void vPWM_DeInit();

/************************************************
*			vPWM_SetFrequency
************************************************/
/* Sets Frequency on all pins
*   @param[in]	uint16_t Frequency in Hz (0..125000)
************************************************/
void vPWM_SetFrequency(float fpFrequency);

/************************************************
*			vPWM_DeInit
************************************************/
/* Sets PWM Duty Cycle of selected pin
*   @param[in]	u8OutputNo	Output number (1..4)
*   @param[in]	fpDutyCycle	Duty cycle in % (0..100)
************************************************/
void vPWM_SetDutyCycle(uint8_t u8OutputNo, float fpDutyCycle);

#endif //_PWM_H_