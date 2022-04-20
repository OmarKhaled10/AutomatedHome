/*
 * KEYBAD.c
 *
 *  Created on: Apr 17, 2021
 *      Author: OMAR
 */
#include "std_types.h"
#include "DIO.h"
#include "KEYBAD.h"

const uint8 arr[4][4]={
		{1,2,3,'a'},
		{4,5,6,'b'},
		{7,8,9,'c'},
		{'*',0,'#','='}
};
uint8 port;
void KEY_vidInit(uint8 u8port_no)
{
	port=u8port_no;
	DIO_vidSetPortDir(u8port_no,OUTPUT);
	DIO_vidSetPinDir(u8port_no,4,INPULLUP);
	DIO_vidSetPinDir(u8port_no,5,INPULLUP);
	DIO_vidSetPinDir(u8port_no,6,INPULLUP);
	DIO_vidSetPinDir(u8port_no,7,INPULLUP);

	DIO_vidWriteOnPin(u8port_no,0,HIGH);
	DIO_vidWriteOnPin(u8port_no,1,HIGH);
	DIO_vidWriteOnPin(u8port_no,2,HIGH);
	DIO_vidWriteOnPin(u8port_no,3,HIGH);
	// 0->3 output (rows)
	// 4->7 input (columns)
}

uint8 KEY_u8GetButton(void)
{

	uint8 temp,flag=0,k=0;
	uint8 i;
	for(i=0;i<4;i++)
	{
		DIO_vidWriteOnPin(port,i,LOW);
		for(uint8 j=0;j<4;j++)
		{
			temp=DIO_u8ReadFromPin(port,j+4);

			if(temp==0)
			{
				k=j;
				flag=1;
				while(!DIO_u8ReadFromPin(port,j+4));
				break;
			}
		}
		DIO_vidWriteOnPin(port,i,HIGH);
		if(flag==1)
		{
			break;
		}
	}

	if(flag==1)
	{
		return arr[i][k];
	}
	else
	{
		return 0xff;
	}
	}
