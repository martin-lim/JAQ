/*--------------------------
File Name	: remote_control.h
Created by	: Martin Lim
Date 		: 05/03/2015
----------------------------*/

#ifndef _REMOTECONTROL_H_
#define _REMOTECONTROL_H_


#define BaudRate 38400
#define BaudPrescale (((F_CPU / (BaudRate*8UL))) - 1)

#include <avr/io.h>
#include "config.h"

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