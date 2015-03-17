/*--------------------------
File Name	: I2C.h
Created by	: Martin Lim
Date 		: 14/03/2015

I2C Class
----------------------------*/
//todo: add time out value

#include "config.h"
#include "I2C.h"

void vI2C_Send(uint16_t u16Address, uint16_t u16Data)
{
	vI2C_StartBit();
	vI2C_WaitACK();
	vI2C_CheckStart();

	vI2C_LoadAddress();
	vI2C_WaitACK();
	vI2C_Check_MT_SLA_ACK();

	vI2C_LoadData();
	vI2C_WaitACK();
	vI2C_Check_MT_DATA_ACK();

	vI2C_StopBit();
}

//send START condition
void vI2C_StartBit()
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
}

//check value of TWI Status Register
void vI2C_CheckStart()
{
	if ((TWSR & 0xF8) != START)
	{
		vI2C_Error();
	}
}

//Load SLA_W into TWDR Register
//Clear TWINT bit in TWCR to start transmission of address
void vI2C_LoadAddress()
{
	TWDR = SLA_W;
	TWCR = (1 << TWINT) | (1 << TWEN);
}

//Check value of TWI Status Register.
void vI2C_Check_MT_SLA_ACK()
{
	if ((TWSR & 0xF8) != MT_SLA_ACK)
	{
		vI2C_Error();
	}
}

//Load DATA into TWDR Register.
//Clear TWINT bit in TWCR to start transmission of data
void vI2C_LoadData()
{
	TWDR = DATA;
	TWCR = (1 << TWINT) | (1 << TWEN);
}

//Wait for TWINT Flag set.
//This indicates that DATA has been transmitted
//and ACK has been received.
void vI2C_WaitACK()
{
	while (!(TWCR & (1 << TWINT)))
	{
	}
}

//Check values of TWI Status Register
//MT_DATA_ACK
void vI2C_Check_MT_DATA_ACK()
{
	if ((TWSR & 0xF8) != MT_DATA_ACK)
	{
		vI2C_Error();
	}
}

//Transmit Stop Condition
void vI2C_StopBit()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void vI2C_Error()
{

}