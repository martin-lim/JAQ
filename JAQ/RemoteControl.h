/*
* RemoteControl.c
*
* Created: 28/06/2014 12:18:00 PM
*  Author: Martin Lim
*/

#ifndef _REMOTECONTROL_H_
#define _REMOTECONTROL_H_

#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__
#endif

#ifndef F_CPU
#define F_CPU 16*10^6UL
#endif

#define BaudRate 38400
#define BaudPrescale (((F_CPU / (BaudRate*8UL))) - 1)

#include <avr/io.h>

/**********************************************************
*			Function Declaration
**********************************************************/
void Remote_init();
void Remote_deinit();

///USART0
void USART0_init(void);
void USART0_send(unsigned char data);
void USART0_sendstring(char* data_StringPtr);
unsigned char USART0_receive(void);
void USART0_flush();


#endif