/*
 * JAQ.c
 *
 * Created: 27/05/2014 8:21:16 PM
 *  Author: Martin Lim
 *
 *	paste code here for testing
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	sei();
	
	//set the pin as output
	//DDRB |= (1<<PORTD6);
	DDRB |= 255;
	DDRC |= 255;
	DDRD |= 255;
	
	
	//set Waveform Generation Mode - PWM Phase Correct
	TCCR2A |= (1<<WGM20)|(1<<COM2A0)|(1<<COM2A1);
	//TCCR2A |= (1<<WGM20)|(1<<COM2A0);//|(1<<COM2A1);
	
	//set Output Compare Value
	OCR2A = 200;
	
	//set Prescale Value - clk/1024
	TCCR2B |= (1<<CS22)|(1<<CS20);
	//TCCR2B |= (1<<CS22)|(1<<CS20)|(1<<WGM22);


		PORTB |= (1<<5);
		_delay_ms(500);
		PORTB &= (0<<5);
		_delay_ms(500);
		
	double DutyCycle = 10;
		
	while (DutyCycle<99)
	{
		
		OCR2A = (DutyCycle/100)*255;
		
		if(DutyCycle==98)
		{
			DutyCycle=10;
		}
		DutyCycle++;
		_delay_ms(50);
	}

		
	
}

