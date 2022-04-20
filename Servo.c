/*
 * Servo.c
 *
 *  Created on: Apr 17, 2021
 *      Author: OMAR
 */
#define F_CPU 8000000UL		/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>		/* Include AVR std. library file */
#include "std_types.h"
#include "Servo.h"

void Ser_vidInti(void)
{
        DDRD |= (1<<PD5);	/* Make OC1A pin as output */
		TCNT1 = 0;		/* Set timer1 count zero */
		ICR1 = 2499;		/* Set TOP count for timer1 in ICR1 register */

		/* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
		TCCR1A = (1<<WGM11)|(1<<COM1A1);
		TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
}

void Ser_vidState(uint8 State)
{
	switch(State)
	{
	case OPEN:
	{
		OCR1A = 175;
		break;
	}
	case CLOSE:
	{
		OCR1A = 300;
			break;
	}
	}
}
