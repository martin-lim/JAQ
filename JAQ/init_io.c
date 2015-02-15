/*
 * init_IO.c
 *
 * Created: 15/02/2012 22:54:33 PM
 *  Author: Shavi
 *  Modify: Martin
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
	#ifdef __AVR_ATmega2560__
		DDRA=0x00;
		PORTA=0x00;
	#endif
	//timer 1A:PB5; timer1B:PB6; timer1C:PB7
	DDRB=( (1<<PB5) |  (1<<PB6) | (1<<PB7) );
	PORTB=0x00;
	
	DDRC=0x00;
	PORTC=0x00;
	
	//set OE signals as high (disable) for initial init, then change status later on
	//PinD0 - OE11; PinD1 - OE12; PinD2 - 9_DOF-Rx; PinD3 - 9_DOF-Tx; PinD4; PinD5; PinD6, PinD7
	DDRD |= ( (1<<PD0) | (1<<PD1) | (1<<PD3) );
	PORTD |= ( (1<<PORTD0) | (1<<PORTD1) | (1<<PORTD4) | (1<<PORTD5) | (1<<PORTD6) | (1<<PORTD7) );

	#ifdef __AVR_ATmega2560__
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
	#endif
}

void init_usart()
{
	/*
	//USART Control and Status Registers
	UCSR0A |= ((1 << RXC0) | (1 << TXC0) | (1 << UDRE0) | (1 << FE0) | (1 << DOR0) | (1 << UPE0) | (1 << U2X0) | (1 << MPCM0));
	UCSR0B |= ((1 << RXCIE0) | (1 << TXCIE0) | (1 << UDRIE0) | (1 << RXEN0) | (1 << TXEN0) | (1 << UCSZ02) | (1 << RXB80) | (1 << TXB80));
	UCSR0C |= ((1 << UMSEL01) | (1 << UMSEL00) | (1 << UPM01) | (1 << UPM00) | (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00) | (1 << UCPOL0));
	UBRR0H =
	UBRR0L =
	*/

	#ifdef __AVR_ATmega2560__
		/*
		// usart0: command
		UCSR0B |= ( (1 << RXEN0) | (1 << TXEN0) ); //enable receiver & transmit
		UCSR0C |= ((1 << UMSEL00) | (1 << UCSZ00) | (1 << UCSZ01));//USART control vector: Synchronous mode with 8 bit data line

		//Baud Rate define in USART.h
		UBRR0H = (BaudPrescale >> 8); //load upper 8 bits of baud rate value to high byte of UBRRH
		UBRR0L = BaudPrescale; // load lower 8 bits to low byte of UBBR register

		//enable Rx interrupt on usart0
		UCSR0B |= (1 << RXCIE0);
		*/

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
	#endif
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
	
	/*
	//8bit timer control registers
	TCCR0A |= ((1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0) | (1 << WGM01) | (1 << WGM00));
	TCCR0B |= ((1 << FOC0A) | (1 << FOC0B) | (1 << WGM02) | (1 << CS02) | (1 << CS01) | (1 << CS00));
	
	//16bit timer control registers
	TCCR1A |= ((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << COM1C1) | (1 << COM1C0) | (1 << WGM11) | (1 << WGM10));
	TCCR1B |= ((1 << ICNC1) | (1 << ICES1) | (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS11) | (1 << CS10));
	TCCR1C |= ((1 << FOC1A) | (1 << FOC1B) | (1 << FOC1C));
	*/

	//timer0 - OC0A/OC0B
	//Waveform Generation Mode
	TCCR0A |= (1 << WGM00); //PWM, Phase Correct (TOP=OCRA, Update of OCRx at = TOP, TOV Flag Set on = BOTTOM
	TCCR0B |= (1 << WGM02);
	//Compare Output Mode
	TCCR0A |= ((1 << COM0A1) | (1 << COM0B1)); //Clear OC0A/OC0B on Compare Match when up-counting. Set OC0A/OC0B on Compare Match when down-counting.
	//Pin Data Direction
	DDRD |= ((1 << PD5) | (1 << PD6)); //set OC0A anf OC0B as outputs
	//Clock Select Bit
	TCCR0B |= ((1 << CS01) | (1 << CS00)); //clkI/O/64 (From prescaler) //TODO: need to calculate right frequency
	//TODO: need to add frequency here
	//TODO: WARNING - need safe initial period and frequency, or else motor spins like crazy
	OCR0A = 254; //frequency
	OCR0B = 10;	//period
}	



//void init_ADC()
/*
 *	//README: connect a 330OHM resistor from ADCIN and 5V and GND
			//USE VOLTAGE DIVIER AND CONENCT TO PIN AIN0
			//V_Batt_status = ACO; 
	
			//comparator = (1.23 * 255) / ADC_data; 
			//ADC_flag = '0'
*/
