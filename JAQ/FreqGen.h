/*
 * FreqGen.h
 *
 * Created: 27/05/2014 8:21:16 PM
 *  Author: Martin Lim
 *
 * This function creates PWM waves
 *
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//set the pin as output
	DDRB |= (1<<PORTD6);
	
	//set Waveform Generation Mode - PWM Phase Correct
	TCCR0A |= (1<<WGM00)|(1<<WGM02)|(1<<COM0A0);
	
	//set Output Compare Value (TOP)
	OCR0A = 255/2;
	
	//set Prescale Value - clk/1024
	TCCR0B |= (1<<CS02)|(1<<CS00);


    while(1)
    {
        

  
    }
}

