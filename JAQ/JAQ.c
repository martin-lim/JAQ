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


	//blinkled - hardware init complete
	for(int i=0; i<3; i++)
	{
		PORTB |= (1<<5);
		_delay_ms(100);
		PORTB &= (0<<5);
		_delay_ms(100);
	}
		
			
	double DutyCycle = 1;	
	//change the duty cycle ever 50ms, for testing	
	while (DutyCycle<100)
	{
		
		OCR2A = (DutyCycle/100)*255;
		//when does this actually update? after timer reset?
		
		if(DutyCycle>=99)
		{
			DutyCycle=1;
		}
		_delay_ms(5);
		DutyCycle++;
	}

		
	
}

