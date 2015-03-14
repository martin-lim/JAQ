/*--------------------------
File Name	: I2C.h
Created by	: Martin Lim
Date 		: 14/03/2015

I2C
----------------------------*/
//todo: add time out value

#include "config.h"
#include "I2C.h"

void vI2C_Start()
{
	//send START condition
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
}

void vI2C_Wait2()
{
	//Wait for TWINT Flag set
	while (!(TWCR & (1 << TWINT)))
		;
}

void vI2C_CheckStart()
{
	//check value of TWI Status Register
	if ((TWSR & 0xF8) != START)
		vI2C_Error();
}

void vI2C_LoadAddress()
{
	//Load SLA_W into TWDR Register
	//Clear TWINT bit in TWCR to start transmission of address
	TWDR = SLA_W;
	TWCR = (1 << TWINT) | (1 << TWEN);
}

void vI2C_Wait1()
{
	//Wait for TWIN flag set
	//This indicates that the SLA+W has been transmitted,
	//and ACK has been received
	while (!(TWCR & (1 << TWINT)))
		;
}

void vI2C_Check_MT_SLA_ACK()
{
	//Check value of TWI Status Register.
	if ((TWSR & 0xF8) != MT_SLA_ACK)
		vI2C_Error();
}

void vI2C_LoadData()
{
	//Load DATA into TWDR Register.
	//Clear TWINT bit in TWCR to start transmission of data
	TWDR = DATA;
	TWCR = (1 << TWINT) | (1 << TWEN);
}

void vI2C_Wait()
{
	//Wait for TWINT Flag set.
	//This indicates that DATA has been transmitted
	//and ACK has been received.
	while (!(TWCR & (1 << TWINT)))
		;
}

void vI2C_Check_MT_DATA_ACK()
{
	//Check values of TWI Status Register
	//MT_DATA_ACK
	if ((TWSR & 0xF8) != MT_DATA_ACK)
		vI2C_Error();
}

void vI2C_Stop()
{
	//Transmit Stop Condition
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void vI2C_Error()
{

}