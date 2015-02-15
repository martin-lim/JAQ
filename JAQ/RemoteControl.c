/*
* RemoteControl.c
*
* Created: 28/06/2014 12:18:00 PM
*  Author: Martin Lim
*
* TODO: learn how to create class and pointers
*/

#include "RemoteControl.h"

/**********************************************************
*			Function Definitions
**********************************************************/

/************************************************
*			Remote_init
************************************************/
void Remote_init()
{
	USART0_init();
}

/************************************************
*			USART0_init
*
* Baud Rate
*	- 38400 (define in header file)
* Speed
*	- 2x speed
* enable Transmit and Receive
* USART Mode Select
*	- Asynchronous UART
* Parity Mode
*	- 1-bit
* Stop Bit Select
*	- Disable,Even,odd
* Character Size (data length)
*	- 8-bit

//additional parameters:
//UCSR0C &= ~((1 << UMSEL01) | (1 << UMSEL00)); //Asynchronous USART
//UCSR0C |= (1 << UPM01) | (1 << UPM00); //Parity Disabled
//UCSR0C &= ~(1 << USBS0); //Stop: 1-bit
//UCSR0B &= ~(1 << UCSZ02); //8-bit
//UCSR0B |= (1 << RXCIE0); //interrupt enabled
************************************************/
void USART0_init()
{
	UBRR0H = (BaudPrescale >> 8); //38400
	UBRR0L = BaudPrescale;
	UCSR0A |= (1 << U2X0); //2x speed
	UCSR0B |= ((1 << RXEN0) | (1 << TXEN0)); //enable Transmit Receive
	UCSR0C |= ((1 << UCSZ01) | (1 << UCSZ00));//8-bit
}

/************************************************
*			USART0_send
************************************************/
void USART0_send(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

/************************************************
*			USART0_sendstring
*
* Keeps sending characters until Null termintaion
* character detected.
*
************************************************/
void USART0_sendstring(char* data_StringPtr)
{
	while (*data_StringPtr != 0x00)
	{
		USART0_send(data_StringPtr);
		data_StringPtr++;
	}
}

/************************************************
*			USART0_receive
************************************************/
unsigned char USART0_receive(void)
{
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

/************************************************
*			USART0_flush
*
* Used to manually flush the receiver buffer FIFO.
* Might be used if an error condition occured.
************************************************/
void USART0_flush(void)
{
	unsigned char dummy;
	while (UCSR0A & (1 << RXC0)) dummy = UDR0;
}
