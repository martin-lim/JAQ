/*--------------------------
File Name	: motors.h
Created by	: Martin Lim
Date 		: 05/03/2015
----------------------------*/
#ifndef _MOTORS_H_
#define _MOTORS_H_

/************************************************
*			vMotor_Arm
************************************************/
void vMotor_Arm();

/************************************************
*			vMotor_Disarm
************************************************/
void vMotor_Disarm();

/************************************************
*			vMotor_SetSpeed
************************************************/
/* Sends value to motor
*   @param[in]	u8MotorNo	Motor number. (1..4)
*   @param[in]	fpOutVal	Output value in %. (0..100)
************************************************/
void vMotor_SetSpeeduint8_t u8MotorNo, float fpOutVal);

#endif //_MOTOR_H_