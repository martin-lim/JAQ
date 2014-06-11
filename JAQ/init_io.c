/*
 * init_IO.c
 *
 * Created: 15/02/2012 22:54:33 PM
 *  Author: Shavi
 *  
 *  bit order: 7654 3210
 *	1 - bit out
 *  0 - bits in
 *	
 *  PORTX HIGH when input - enable internal pullup
 *  PORTX HIGH when output - drive port HIGH
 *
 *  unused PINS should have pullup's enabled
 *  PORTA |= (1<<PORTA7); //set bit 7 port a
 *  PORTA &= ~(1<<PORTA7); //unset bit 7 port a
 *  PORTA & (1<<PORTA7); //check bit
 *  
 *  AIN - PE3,PE2
 *   *  
 *	TIMERS OUT:
 *	OE11: PD1 - Must be set low to enable
 *	OE12: PD0 - Must be set low to enable
 *	OE21: PH7 - Must be set low to enable
 *	OE22: PL0 - Must be set low to enable
 *	
 *	PWM1: PH5 (timer4c)
 *	PWM2: PH4 (timer4b)
 *	PWM3: PB5 (timer1A)
 *	PWM4: PB6 (timer1B)
 *	PWM5: PB7 (timer1c)
 *	PWM6: PL3 (timer5a)
 *	PWM7: PL4 (timer5b)
 *	PWM8: PL5 (timer5c)
 *	PWM9: PH3 (timer4a)
 *	PWM10: PE5 (timer3c)
 *	PWM11: PE4 (timer3b)
 *	PWM12: PE3 (timer3a)
 *	
 */ 

#include "init_io.h"

void init_IO()
{
    DDRA=0x00;
	PORTA=0x00;

	//timer 1A:PB5; timer1B:PB6; timer1C:PB7
	DDRB=( (1<<PB5) |  (1<<PB6) | (1<<PB7) );
	PORTB=0x00;
	
	DDRC=0x00;
	PORTC=0x00;
	
	//set OE signals as high (disable) for initial init, then change status later on
	//PinD0 - OE11; PinD1 - OE12; PinD2 - 9_DOF-Rx; PinD3 - 9_DOF-Tx; PinD4; PinD5; PinD6, PinD7
	DDRD |= ( (1<<PD0) | (1<<PD1) | (1<<PD3) );
	PORTD |= ( (1<<PORTD0) | (1<<PORTD1) | (1<<PORTD4) | (1<<PORTD5) | (1<<PORTD6) | (1<<PORTD7) );

	//pe0:rx, pe1:tx; pe3:timer3a; pe4:timer4a; pe5:timer5a
	DDRE=( (1<<PE1) | (1<<PE3) | (1<<PE4) | (1<<PE5)); //PE0 - RXDO, PE1 - TXD0
	PORTE=0x00;
	
	DDRF=0x00;
	PORTF=0x00;
	
	//PortG5: switch input, enable pullup resistor;
	DDRG=0x00;
	PORTG=( (1<<PORTG5) );
	
	// timer4a: ph3; timer4b: ph4; timer4c:ph5; OE21: PH7
	DDRH=( (1<<PH3) | (1<<PH4) | (1<<PH5) | (1<<PH7) );
	PORTH=0x00;

	DDRJ=0x00;
	PORTJ=0x00;
	
	//portK3: first gpio set to high;
	DDRK=( (1<<PK3) );
	PORTK=( (1<<PORTK3) ); 

	//pl0: oe22
	DDRL=( (1<<PL0) );
	PORTL=0x00;
}

void init_usart()
{
	//BaudRate: 57600
	
	// usart0: command
	UCSR0B |= ((1<<RXEN0) | (1<<TXEN0)); //enable receiver & transmit
	UCSR0C |= ( (1<<UMSEL00) | (1<<UCSZ00) | (1<<UCSZ01) );//USART control vector: Synchronous mode with 8 bit data line
	
	//Baud Rate define in USART.h
	UBRR0H = (BaudPrescale >> 8); //load upper 8 bits of baud rate value to high byte of UBRRH
	UBRR0L = BaudPrescale; // load lower 8 bits to low byte of UBBR register
	
	//enable Rx interrupt on usart0
	UCSR0B |= (1<<RXCIE0);
	
	// usart1:
	UCSR1B |= (1<<RXEN0); //enable receiver
	UCSR1C |= ( (1<<UMSEL10) | (1<<UCSZ10) | (1<<UCSZ11) );//USART control vector: Synchronous mode with 8 bit data line

	//Baud Rate define in USART.h
	UBRR1H = (BaudPrescale >> 8); //load upper 8 bits of baud rate value to high byte of UBRRH
	UBRR1L = BaudPrescale; // load lower 8 bits to low byte of UBBR register
	
	//enable Rx interrupt on usart1
	UCSR1B |= (1<<RXCIE1);
	
	// usart2:
	UCSR2B |= (1<<RXEN0); //enable receiver
	UCSR2C |= ( (1<<UMSEL20) | (1<<UCSZ20) | (1<<UCSZ21) );//USART control vector: Synchronous mode with 8 bit data line

	//Baud Rate define in USART.h
	UBRR2H = (BaudPrescale >> 8); //load upper 8 bits of baud rate value to high byte of UBRRH
	UBRR2L = BaudPrescale; // load lower 8 bits to low byte of UBBR register
	
}

void init_timers() 
{
	/* PWM setup: http://www.atmel.com/Images/doc2505.pdf
	 * fPWM = (fcpu/pValr(1+OVFL) ) => (16x10^6 / 64*(1+OVFL)) => OVFL(ICR)=4999
	 * PWM freq = 50Hz, 1/f = 0.02s, ie 20ms.
	 *
	 * need 40khz signal for sonar timer: 8-bit: OCR: 0x32, prescaler: 8, (1<<CS01)
	 * set 16-bit timers (1,3,4,5) up as non inverting, with a prescaler of 64, ie fast pwm
	*/
	
	//timer1
	TCCR1A |= ( (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11) ); 
	TCCR1B |= ( (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10) );
	ICR1 = 4999; //PWM freq
	//just to be sure, set pins as out
	DDRB |= ( (1<<PB5) | (1<<PB7) | (1<<PB7) );
	
	//timer3
	TCCR3A |= ( (1<<COM3A1) | (1<<COM3B1) | (1<<WGM31) ); 
	TCCR3B |= ( (1<<WGM33) | (1<<WGM32) | (1<<CS31) | (1<<CS30) ); 
	ICR3 = 4999; 
	DDRE |= ( (1<<PE3) | (1<<PE4) | (1<<PE5) );
	
	//timer4
	TCCR4A |= ( (1<<COM4A1) | (1<<COM4B1) | (1<<WGM41) ); 
	TCCR4B |= ( (1<<WGM43) | (1<<WGM42) | (1<<CS41) | (1<<CS40) ); 
	ICR4 = 4999;
	DDRH |= ( (1<<PH3) | (1<<PH4) | (1<<PH5) );
	
	//timer5
	TCCR5A |= ( (1<<COM5A1) | (1<<COM5B1) | (1<<WGM51) ); 
	TCCR5B |= ( (1<<WGM53) | (1<<WGM52) | (1<<CS51) | (1<<CS50) ); 
	ICR5 = 4999; 
	DDRL |= ( (1<<PL3) | (1<<PL4) | (1<<PL5) );
	
}	



//void init_ADC()
/*
 *	//README: connect a 330OHM resistor from ADCIN and 5V and GND
			//USE VOLTAGE DIVIER AND CONENCT TO PIN AIN0
			//V_Batt_status = ACO; 
	
			//comparator = (1.23 * 255) / ADC_data; 
			//ADC_flag = '0'
*/
