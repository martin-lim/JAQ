/*
 * JAQ.c
 *
 * Created: 1/06/2014 10:26:00 PM
 *  Author: Shavi
 *  Edit: Martin
 */ 

#define TESTONLY

#include "jaq.h"

int main(void)
{
	init_IO();
	Remote_init();
	Motor_arm();

	char data[] = "Testing";

	while(1)
	{
#ifdef TESTONLY

		for (int i = 0; i < 3; i++)
		{
			for (uint16_t pwm_duty = 0; pwm_duty < 0xFFFF; pwm_duty++)
			{
				Motor_drive(1, pwm_duty);
				Motor_drive(2, pwm_duty + 0x000F);
				Motor_drive(3, pwm_duty + 0x00FF);
				Motor_drive(4, pwm_duty + 0x0FFF);
			}
		}

		USART0_sendstring(data);
		
		//blink led
		PORTB |= (1 << PB5);
		_delay_ms(500);
		PORTB &= ~(1 << PB5);
		_delay_ms(500);
#endif
    }
}