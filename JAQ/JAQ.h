/*
 * jaq.h
 *
 * Created: 16/02/2012 1:20:46 AM
 * Last Modified : 02/06/2014
 *  Author: Shavi Nachman
 *  Modified: Martin Lim
 */ 
 #ifndef _JAQ_H_
	#define _JAQ_H_

	#ifndef __AVR_ATmega328__
	#define __AVR_ATmega328__
	#endif

	//Project menu > Project Properties (Alt+F7) > Toolchain > AVR/GNU C Compiler > Symbols > Add F_CPU=16000000UL to Defined Symbols
	//main clock define
	#ifndef F_CPU
	#define F_CPU 16*10^6UL
	#endif

	#define CYCLES_PER_US ((F_CPU+500000)/1000000)
	#define __DOXYGEN__

	//standard library
	#include <avr/io.h>
	#include <stdint.h>
	//#include <avr/interrupt.h>

	//custom library
	#include "init_io.h"
	/*
	#include "stabilityControl.h"
	#include "motorControl.h"
	*/

	int main(void);
	
#endif
 
