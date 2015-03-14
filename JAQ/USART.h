/*--------------------------
File Name	: USART.h
Created by	: Martin Lim
Date 		: 05/03/2015

UART driver for Atmega2560 
----------------------------*/
#ifndef _USART_H_
#define _USART_H_

#include "config.h"

void vUSART_SetBaud();
void vUSART_SetParity();
void vUSART_Init();
void vUSART_Send();
void vUSART_SendString();
void vUSART_Receive();
void vUSART_Clear();


#endif //_USART_H_