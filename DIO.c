/*
 * DIO.c
 *
 *  Created on: Apr 10, 2021
 *      Author: OMAR
 */
#include "std_types.h"
#include "Utils.h"
#include "DIO.h"
#include <avr/io.h>



void DIO_vidSetPinDir (uint8 u8port_no,uint8 u8pin_no,uint8 u8dir)
{
	switch(u8dir)
	{
	case OUTPUT:
	{
		switch(u8port_no)
		{
		case PA:
		{
			SetBit(DDRA,u8pin_no);
			break;
		}
		case PB:
		{
			SetBit(DDRB,u8pin_no);
			break;
		}
		case PC:
		{
			SetBit(DDRC,u8pin_no);
			break;
		}
		case PD:
		{
			SetBit(DDRD,u8pin_no);
			break;
		}
		default:
		{
			/*do no thing */
			break;
		}
		}
		break;
	}
	case INFREE:
	{
		switch(u8port_no)
		{
		case PA:
		{
			ClrBit(DDRA,u8pin_no);
			break;
		}
		case PB:
		{
			ClrBit(DDRB,u8pin_no);
			break;
		}
		case PC:
		{
			ClrBit(DDRC,u8pin_no);
			break;
		}
		case PD:
		{
			ClrBit(DDRD,u8pin_no);
			break;
		}
		default:
		{
			/*do no thing */
			break;
		}
		}
		break;
	}
	case INPULLUP:
	{
		switch(u8port_no)
		{
		case PA:
		{
			ClrBit(DDRA,u8pin_no);
			SetBit(PORTA,u8pin_no);
			break;
		}
		case PB:
		{
			ClrBit(DDRB,u8pin_no);
			SetBit(PORTB,u8pin_no);
			break;
		}
		case PC:
		{
			ClrBit(DDRC,u8pin_no);
			SetBit(PORTC,u8pin_no);
			break;
		}
		case PD:
		{
			ClrBit(DDRD,u8pin_no);
			SetBit(PORTD,u8pin_no);
			break;
		}
		default:
		{
			/*do no thing */
			break;
		}
		}
		break;
	}
	default:
	{
		/*do no thing*/
		break;
	}
	}
}
/*--------------------------------------------*/
void DIO_vidSetPortDir(uint8 u8port_no,uint8 u8dir)
{
	switch(u8dir)
	{
	case OUTPUT:
	{
		switch(u8port_no)
		{
		case PA:
		{
			DDRA=0xff;
			break;
		}
		case PB:
		{
			DDRB=0xff;
			break;
		}
		case PC:
		{
			DDRC=0xff;
			break;
		}
		case PD:
		{
			DDRD=0xff;
			break;
		}
		default:
		{
			/*do no thing */
			break;
		}
		}
		break;
	}
	case INFREE:
	{
		switch(u8port_no)
		{
		case PA:
		{
			DDRA=0x00;
			break;
		}
		case PB:
		{
			DDRB=0x00;
			break;
		}
		case PC:
		{
			DDRC=0x00;
			break;
		}
		case PD:
		{
			DDRD=0x00;
			break;
		}
		default:
		{
			/*do no thing */
			break;
		}
		}
		break;
	}
	case INPULLUP:
	{
		switch(u8port_no)
		{
		case PA:
		{
			DDRA=0x00;
			PORTA=0xff;
			break;
		}
		case PB:
		{
			DDRB=0x00;
			PORTB=0xff;
			break;
		}
		case PC:
		{
			DDRC=0x00;
			PORTC=0xff;
			break;
		}
		case PD:
		{
			DDRD=0x00;
			PORTD=0xff;
			break;
		}
		default:
		{
			/*do no thing */
			break;
		}
		}
		break;
	}
	default:
	{
		/*do no thing*/
		break;
	}
	}
}
/*---------------------------------------*/
void DIO_vidWriteOnPin (uint8 u8port_no,uint8 u8pin_no,uint8 u8level)
{
	switch(u8level)
	{
	case HIGH:
	{
		switch(u8port_no)
		{
		case PA:
		{
			SetBit(PORTA,u8pin_no);
			break;
		}
		case PB:
		{
			SetBit(PORTB,u8pin_no);
			break;
		}
		case PC:
		{
			SetBit(PORTC,u8pin_no);
			break;
		}
		case PD:
		{
			SetBit(PORTD,u8pin_no);
			break;
		}
		default:
		{
			/*do nothing*/
			break;
		}
		}
		break;
	}
	case LOW:
	{
		switch(u8port_no)
		{
		case PA:
		{
			ClrBit(PORTA,u8pin_no);
			break;
		}
		case PB:
		{
			ClrBit(PORTB,u8pin_no);
			break;
		}
		case PC:
		{
			ClrBit(PORTC,u8pin_no);
			break;
		}
		case PD:
		{
			ClrBit(PORTD,u8pin_no);
			break;
		}
		default:
		{
			/* do nothing*/
			break;
		}
		}
		break;
		default:
		{
			/*do nothing */
			break;
		}
	}
	}
}
/*------------------------------------------------*/
void DIO_vidWrireOnPort (uint8 u8port_no,uint8 u8data)
{
	switch(u8port_no)
	{
	case PA:
	{
		PORTA=u8data;
		break;
	}
	case PB:
	{
		PORTB=u8data;
		break;
	}
	case PC:
	{
		PORTC=u8data;
		break;
	}
	case PD:
	{
		PORTD=u8data;
		break;
	}
	default:
	{
		/*do nothing*/
		break;
	}
	}
}
/*------------------------------------------------*/
uint8 DIO_u8ReadFromPin (uint8 u8port_no,uint8 u8pin_no)
{
	uint8 x;
	switch(u8port_no)
	{
	case PA:
	{
		x=GetBit(PINA,u8pin_no);
		break;
	}
	case PB:
	{
		x=GetBit(PINB,u8pin_no);
		break;
	}
	case PC:
	{
		x=GetBit(PINC,u8pin_no);
		break;
	}
	case PD:
	{
		x=GetBit(PIND,u8pin_no);
		break;
	}
	}
	return x;
}
/*------------------------------------------------*/
uint8 DIO_u8ReadFromPort (uint8 u8Port_no)
{
	uint8 x;
	switch(u8Port_no)
	{
	case PA:
	{
		x=PINA;
		break;
	}
	case PB:
	{
		x=PINB;
		break;
	}
	case PC:
	{
		x=PINC;
		break;
	}
	case PD:
	{
		x=PIND;
		break;
	}
	}
	return x;
}
