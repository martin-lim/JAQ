/*--------------------------
File Name	: PWM.h
Created by	: Martin Lim
Date 		: 05/03/2015

PWM timer library for ATMEGA2560
----------------------------*/

#ifndef _PWM_H_
#define _PWM_H_

void vCounters_Init();
void vCounters_DeInit();
void vPWM_SetFrequency(uint16_t u16Frequency);
void vPWM_SetDutyCycle(uint8_t u8OutputNo, float fpDutyCycle);

/*
void Timer_Init(uint16_t pwmFrequency, uint16_t pwmDuty); //default: 65532, 10
void Timer_Deinit();
void Timer_To_Pin();
void Timer_Set_Value(uint8_t outputNumber, uint16_t value);
*/ //removed 11.03.15

#endif //_TIMERS_H_