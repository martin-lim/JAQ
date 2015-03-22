/*--------------------------
File Name	: I2C.h
Created by	: Martin Lim
Date 		: 14/03/2015

I2C Class
----------------------------*/
//todo: add time out value

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

/************************************************
*			I2C_vStart
************************************************/
/* Tramsmit start condition
************************************************/
void I2C_vStart()
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
}

/************************************************
*			I2C_vWaitACK
************************************************/
/* Wait for TWINT Flag set.
*  This indicates data has been transmitted
*  and ACK has been received.
************************************************/
void I2C_vWaitACK()
{
	while (!(TWCR & (1 << TWINT)))
	{
		//TODO:add timeout
	}
}

/************************************************
*			I2C_vCheckStart
************************************************/
/* Check value of TWI Status Register.
*  Check if start ackknowledge received.
************************************************/
void I2C_vCheckStart()
{
	if ((TWSR & 0xF8) != START)
	{
		I2C_vError();
	}
}

/************************************************
*			I2C_vLoadAddress
************************************************/
/* Load 7-bit address TWDR Register.
*  Load 1-bit control bit into TWDR Register
*  Clear TWIN bit in TWCR to start transmission.
************************************************/
void I2C_vLoadAddress(uint8_t u8Address)
{
	uint8_t SLA_W = (u8Address << 1); //7bit address 
	SLA_W &= ~(1 << 0);	//1bit control flag = 0
	TWDR = SLA_W;
	TWCR = (1 << TWINT) | (1 << TWEN);
}

/************************************************
*			I2C_vCheck_MT_SLA_ACK
************************************************/
/* Check value of TWI Status Register.
*  Check if MT_SLA ackknowledge received.
************************************************/
void I2C_vCheck_MT_SLA_ACK()
{
	if ((TWSR & 0xF8) != MT_SLA_ACK)
	{
		I2C_vError();
	}
}

/************************************************
*			I2C_vLoadData
************************************************/
/* Load DATA into TWDR Register.
*  Clear TWIN bit in TWCR to start transmission.
************************************************/
void I2C_vLoadData(uint8_t u8Data)
{
	TWDR = u8Data;
	TWCR = (1 << TWINT) | (1 << TWEN);
}

/************************************************
*			I2C_vCheck_MT_DATA_ACK
************************************************/
/* Check value of TWI Status Register.
*  Check if MT_Data Ackknowledge received.
************************************************/
void I2C_vCheck_MT_DATA_ACK()
{
	if ((TWSR & 0xF8) != MT_DATA_ACK)
	{
		I2C_vError();
	}
}

/************************************************
*			I2C_vSendStop
************************************************/
/* Transmit Stop Condition
************************************************/
void I2C_vStop()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

/************************************************
*			I2C_vError
************************************************/
/* Error Handling
************************************************/
void I2C_vError()
{

}

/************************************************
*			I2C_vTransmit
************************************************/
/* Transmit 8 bit data to 7 bit address
************************************************/
void I2C_vTransmit(uint8_t u8Address, uint8_t u8Data)
{
	//Start
	I2C_vStart();
	I2C_vWaitACK();
	I2C_vCheckStart();
	//Address + Mode
	I2C_vLoadAddress(u8Address);
	I2C_vWaitACK();
	I2C_vCheck_MT_SLA_ACK();
	//Data
	I2C_vLoadData(u8Data);
	I2C_vWaitACK();
	I2C_vCheck_MT_DATA_ACK();
	//Stop
	I2C_vStop();
}