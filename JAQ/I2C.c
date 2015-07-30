/*--------------------------
File Name	: I2C.h
Created by	: Martin Lim
Date 		: 14/03/2015

I2C Class
----------------------------*/

#include "config.h"
#include "I2C.h"

//Master Transmit Status Codes
#define START			0x08
#define START_REP		0x10
#define MT_SLA_ACK		0x18
#define MT_SLA_NACK		0x20
#define MT_DATA_ACK		0x28
#define MT_DATA_NACK	0x30
#define LOST			0x38

//Master Receive Status Codes
#define MR_SLA_ACK		0x40
#define MR_SLA_NACK		0x48
#define MR_DATA_ACK		0x50
#define MR_DATA_NACK	0x58

/************************************************
*			I2C_vInit
************************************************/
/* Init I2C Settings
************************************************/
void I2C_vInit()
{
  //I2C_PULLUPS_DISABLE
  TWSR = 0; //no prescaler => prescaler = 1
  TWBR = ((F_CPU / 400000) - 16) / 2; //400kHz
  TWCR = ( 1<<TWEN );
 }

/************************************************
*			I2C_vError
************************************************/
/* Error Handling
************************************************/
void I2C_vError()
{
	//TODO: send to serial monitor
}

/************************************************
*			I2C_u8GetStatus
/************************************************/
/* Wait for TWINT Flag set.
*  This indicates data has been transmitted and
*  ACK has been received.
*  Return value of TWI Status Register (TWSR).
************************************************/
uint8_t I2C_u8GetStatus()
{	
	while (!(TWCR & (1 << TWINT))) //TODO: add timeout
	{
	}
	return (TWSR & 0xF8); 
}

/************************************************
*			I2C_vStart
************************************************/
/* Tramsmit start condition
*  Check if MT_SLA_ACK received
************************************************/
void I2C_vStart()
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	
	if (I2C_u8GetStatus() != START)
	{
		I2C_vError();
	}
}

/************************************************
*			I2C_vLoadWriteAddress
************************************************/
/* Load 7-bit address TWDR Register.
*  Load 1-bit control bit into TWDR Register
*  Clear TWIN bit in TWCR to start transmission.
*  Check if MT_SLA_ACK received
************************************************/
void I2C_vLoadWriteAddress(uint8_t u8Address)
{
	uint8_t SLA_W = (u8Address << 1); //7bit address 
	SLA_W &= ~(1 << 0);	//1bit control flag = 0
	TWDR = SLA_W;
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	if (I2C_u8GetStatus() != MT_SLA_ACK)
	{
		I2C_vError();
	}
}

/************************************************
*			I2C_vLoadReadAddress
************************************************/
/* Load 7-bit address TWDR Register.
*  Load 1-bit control bit into TWDR Register
*  Clear TWIN bit in TWCR to start transmission.
*  Check if MR_SLA_ACK received.
************************************************/
void I2C_vLoadReadAddress(uint8_t u8Address)
{
	uint8_t SLA_W = (u8Address << 1); //7bit address 
	SLA_W |= (1 << 0);	//read = 1, write = 0
	TWDR = SLA_W;
	TWCR = (1 << TWINT) | (1 << TWEN);

	if (I2C_u8GetStatus() != MR_SLA_ACK)
	{
		I2C_vError();
	}
}

/************************************************
*			I2C_vLoadData
************************************************/
/* Load DATA into TWDR Register.
*  Clear TWIN bit in TWCR to start transmission.
*  Check if MT_DATA_ACK received
************************************************/
void I2C_vLoadData(uint8_t u8Data)
{
	TWDR = u8Data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	if (I2C_u8GetStatus() != MT_DATA_ACK)
	{
		I2C_vError();
	}
}

/************************************************
*			I2C_vSendACK
************************************************/
/* Sends ACK or NACK
************************************************/
void I2C_vSendACK(bool boACK)
{
	if (boACK == 1) 
	{
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); //ACK
	}
	else
	{	
		TWCR = (1 << TWINT) | (1 << TWEN); //NACK
	}
}

/************************************************
*			I2C_vReadData
************************************************/
/* Sends signal to slave to transmit data.
*  Waits and check for ACK.
*  Stores Data in buffer (pointer).
*  Sends NACK signal to indicated last byte.
*  Waits and check for NACK.
*  Stores Data in pointer.
************************************************/
void I2C_vReadData(uint8_t *u8Buffer, uint8_t u8Size)
{
	while (u8Size--)
	{
		if(u8Size!=0)
		{
			I2C_vSendACK(1); //get more bytes, send ACK
			if(I2C_u8GetStatus() != MR_DATA_ACK)
			{
				I2C_vError();
			}
		}
		else
		{
			I2C_vSendACK(0); //get last byte, send NACK	
			if(I2C_u8GetStatus() != MR_DATA_NACK)
			{
				I2C_vError();
			}
		}

		*u8Buffer++ = TWDR; //Read from Data Register
	}
}

/************************************************
*			I2C_vStop
************************************************/
/* Transmit Stop Condition
************************************************/
void I2C_vStop()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

/************************************************
*			I2C_vUnitTest
************************************************/
/* (Dont Run) For Testing only
************************************************/
void vUnitTest()
{
	I2C_vInit();

	/* Master Transmit 8 bit data */
	I2C_vStart();
	I2C_vLoadWriteAddress(0xFF);
	I2C_vLoadData(0xAA);
	I2C_vStop();

	/* Master Receive 8 bit data */
	uint8_t u8MyBuffer[1];
	I2C_vStart();
	I2C_vLoadReadAddress(0xFF);
	I2C_vReadData(u8MyBuffer, 1);
	I2C_vStop();

	/* Master Receive 7 bytes data */
	uint8_t u8MyBuffer2[7];
	I2C_vStart();
	I2C_vLoadReadAddress(0xFF);
	I2C_vReadData(u8MyBuffer2, 7);
	I2C_vStop();

	/* Reading Slave Registers */
	//Write to register
	I2C_vStart();
	I2C_vLoadWriteAddress(0xFF);
	I2C_vLoadData(0xAA);
	//Read Data (2 bytes expected)
	uint8_t u8ValueADC;
	I2C_vLoadReadAddress(0xFF);
	I2C_vReadData(&u8ValueADC, 2);
	I2C_vStop();
	
	
}
