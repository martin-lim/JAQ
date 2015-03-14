/*--------------------------
File Name	: motors.c
Created by	: Martin Lim
Date 		: 06/03/2015
----------------------------*/

#include "motors.h"
#include "PWM.h"
#include "config.h"

#define PWM_ARM 0.1 //TOOD: move this somewhere
#define PWM_SAFE 0.1

/************************************************
*			vTest
************************************************/
void vTest()
{
	//for testing purposes only
	vMotor_Arm();
	vMotor_Set(1, PWM_ARM);
	vMotor_Set(1, PWM_SAFE);
}

/************************************************
*			vMotor_Arm
************************************************/
void vMotor_Arm()
{
	vPWM_Init();
	vPWM_SetFrequency(400);	//400Hz
	vPWM_SetDutyCycle(1, PWM_ARM);
	vPWM_SetDutyCycle(2, PWM_ARM);
	vPWM_SetDutyCycle(3, PWM_ARM);
	vPWM_SetDutyCycle(4, PWM_ARM);
}

/************************************************
*			vMotor_Disarm
************************************************/
void vMotor_Disarm()
{
	vPWM_DeInit();
}

/************************************************
*			vMotor_SetSpeed
************************************************/
void vMotor_SetSpeed(uint8_t u8MotorNo, float fpOutVal)
{
	vPWM_SetDutyCycle(u8MotorNo, fpOutVal);
}