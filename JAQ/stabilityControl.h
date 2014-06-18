/*
 * stability_control.h
 *
 * Created: 16/02/2012 1:19:26 PM
 *  Author: Shavi
 */ 

#ifndef _STABILITY_CONTROL_H_
	#define _STABILITY_CONTROL_H_
	
	#include <string.h>
	#include <stdio.h>
	#include <avr/interrupt.h>
	#include "init_io.h"
	#include "motorControl.h"
	//#include "usart.h"
	
	//Sweetest points
	#define SweetSpotX 180
	#define SweetSpotY 180
	
	//Servo limits
	#define Servo1FLLX_HIGH 255
	#define Servo1FLLX_LOW 150
		

	//accelerometer limits
	#define ACCELX_HIGH 255
	#define ACCELX_LOW 150
	
	#define ACCELY_HIGH 255
	#define ACCELY_LOW 150
	
	#define ACCELZ_HIGH 255
	#define ACCELZ_LOW 150
	
	//gyroscope limits
	#define GYROX_HIGH 255
	#define GYROX_LOW 150
	
	#define GYROY_HIGH 255
	#define GYROY_LOW 150
	
	#define GYROZ_HIGH 255
	#define GYROZ_LOW 150
	
	//magnetometer limits
	#define MAGX_HIGH 255
	#define MAGX_LOW 150
	
	#define MAGY_HIGH 255
	#define MAGY_LOW 150
	
	#define MAGZ_HIGH 255
	#define MAG_LOW 150
	
	
	
	typedef struct AXIS_SENSORS {	
		int16_t accelx;  
		int16_t accely;
		int16_t accelz;

		int16_t gyrox;
		int16_t gyroy;
		int16_t gyroz;

		int16_t magx;
		int16_t magy;
		int16_t magz;
	}Sensors;
	
	void calculator(void);
#endif