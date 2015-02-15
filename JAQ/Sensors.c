/*
* Sensors.c
*
* Created: 04/07/2014 3:03:00 PM
*  Author: Martin Lim
*
*/


#include "Sensors.h"

/**********************************************************
*			Function Definitions
**********************************************************/

/************************************************
*			I2C
************************************************/
void I2C()
{
	//Send START condition
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	
	//wait for TWINT flag set
	while (!(TWCR & (1 << TWINT)));

	//Check valye of TWI Status Register
	//Mask status bit
	if ((TWSR & 0xF8) != START)
	{
		ERROR();
	}

	//Load SLA_W into TWRD Register
	//Clear TWINT bit in TWCR to start transmission of address 
	TWDR = SLA_W;
	TWCR = (1 << TWINT) | (1 << TWEN); 
	
	//Wait for TWINT Flag set //ACK received
	while (!(TWCR & (1 << TWINT)));

	//Check value of TWI Status Register
	if ((TWSR & 0xF8) != MT_SLA_ACK) //Check value of TWI Status Register
	{
		ERROR();
	}

	TWDR = DATA;	//Load DATA into TWDR Register.
	TWCR = (1 << TWINT) | (1 << TWEN);	//Clear TWINT bit in TWCR to start transmission of data

	while (!(TWCR & (1 << TWINT)))
	{ //Wait for TWINT Flag set //ACK received
	}

	if ((TWSR & 0xF8) != MT_DATA_ACK) //Check value of TWI Status Register
	{
		ERROR();
	}

	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); //Transmit STOP condition


}