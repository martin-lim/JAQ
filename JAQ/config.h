/*--------------------------
File Name	: config.h
Created by	: Martin Lim
Date 		: 05/03/2015

use this file to configure:
1. microcontroller type
2. CPU Clock
3. Motors
4. Timers
----------------------------*/

#ifndef _CONFIG_H_
#define _CONFIG_H_

/* Microcontroller */
#define __AVR_ATmega2560__ //temporary
//#define __AVR_ATmega328p__ //temporary

/* CPU Clock */
//#define F_CPU 16*10^6UL
#define F_CPU 16000000

/* Motors */
//number of motors

/* Timers */
//#define pwm max_value
//#define pwm min_value

//AVR libraries
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#endif