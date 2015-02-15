/*
 * init_io.h
 *
 * Created: 14/02/2012 8:39:46 PM
 *  Author: Shavi
 */ 
 
 #ifndef _INIT_IO_H_
	#define _INIT_IO_H_

	#ifndef __AVR_ATmega328__
	#define __AVR_ATmega328__
	#endif

	#include <avr/io.h>
	//#include "USART.h"
	//#include "ADC.h"
	//#include "ADComparator.h"

	#ifndef F_CPU
		#define F_CPU 16*10^6UL
	#endif
	
	void init_IO(void);
	void init_usart(void);
	void init_timers(void);
	
#endif /* INIT_IO_H_ */

 
 
 