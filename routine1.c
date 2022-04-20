/*
 * routine.c
 *
 *  Created on: Apr 27, 2021
 *      Author: OMAR
 */

#include "std_types.h"
#include "common_macros.h"
#include "routine1.h"
#include "micro_config.h"


uint16 sync[3] = {0};
uint8 status[3]= {done};

uint8 sync_flag[3] = {0};

//sint16*  LED1[3]={PORTA , PORTB , PORTC};
//sint16*  LED2[3]={PORTA , PORTB , PORTC};
//sint16*  FAN[3]={PORTA , PORTB , PORTC};


void Clear_Routine_Flags(uint8 user)
{
	if(user != 4)
	{
		sync_flag[(user - 1)] = 0;
	}
	else
	{
		sync_flag[0] = 0;
		sync_flag[1] = 0;
		sync_flag[2] = 0;
	}

}


uint8 Get_status(uint8 user)
{
	return status[(user - 1)];
}


void Do_Routine(uint8 seconds , uint8 user , uint8 LED1_enable , uint8 LED1_start , uint8 LED1_end , uint8 LED2_enable , uint8 LED2_start , uint8 LED2_end , uint8 FAN_enable , uint8 FAN_start , uint8 FAN_end)
{
	user--;

	if( (sync_flag[user] == 0) )
	{
		sync[user] = seconds;			//sync
		status[user] = onit;			//status

		sync_flag[user] = 1;
	}

	//LED1 routine
	if( (LED1_enable == 1) )
	{
		if(seconds >= (LED1_start + sync[user]))		// [LED_start , LED_end]
		{
			//turn LED on
			switch(user)
			{
			case 0:
				SET_BIT(LED1_user1_port,LED1_user1_pin);
				break;
			case 1:
				SET_BIT(LED1_user2_port,LED1_user2_pin);
				break;
			case 2:
				SET_BIT(LED1_user3_port,LED1_user3_pin);
				break;
			}

		}
		if(seconds >= (LED1_end + sync[user]))
		{
			//turn LED off
			switch(user)
			{
			case 0:
				CLEAR_BIT(LED1_user1_port,LED1_user1_pin);
				break;
			case 1:
				CLEAR_BIT(LED1_user2_port,LED1_user2_pin);
				break;
			case 2:
				CLEAR_BIT(LED1_user3_port,LED1_user3_pin);
				break;
			}
		}
	}

	//LED2 routine
	if( (LED2_enable == 1) )
	{
		if(seconds >= (LED2_start + sync[user]))		// [LED_start , LED_end]
		{
			//turn LED2 on
			switch(user)
			{
			case 0:
				SET_BIT(LED2_user1_port,LED2_user1_pin);
				break;
			case 1:
				SET_BIT(LED2_user2_port,LED2_user2_pin);
				break;
			case 2:
				SET_BIT(LED2_user3_port,LED2_user3_pin);
				break;
			}
		}
		if(seconds >= (LED2_end + sync[user]))
		{
			//turn LED2 off
			switch(user)
			{
			case 0:
				CLEAR_BIT(LED2_user1_port,LED2_user1_pin);
				break;
			case 1:
				CLEAR_BIT(LED2_user2_port,LED2_user2_pin);
				break;
			case 2:
				CLEAR_BIT(LED2_user3_port,LED2_user3_pin);
				break;
			}
		}
	}

	//FAN routine
	if( (FAN_enable == 1) )
	{
		if(seconds >= (FAN_start + sync[user]))		// [LED_start , LED_end]
		{
			//turn FAN on
			switch(user)
			{
			case 0:
				CLEAR_BIT(FAN_user1_port,FAN_user1_pin);
				break;
			case 1:
				CLEAR_BIT(FAN_user2_port,FAN_user2_pin);
				break;
			case 2:
				CLEAR_BIT(FAN_user3_port,FAN_user3_pin);
				break;
			}
		}
		if(seconds >= (FAN_end + sync[user]))
		{
			//turn FAN off
			switch(user)
			{
			case 0:
				SET_BIT(FAN_user1_port,FAN_user1_pin);
				break;
			case 1:
				SET_BIT(FAN_user2_port,FAN_user2_pin);
				break;
			case 2:
				SET_BIT(FAN_user3_port,FAN_user3_pin);
				break;
			}
		}
	}

	if( (seconds >= (LED1_end + sync[user])) && (seconds >= (LED2_end + sync[user])) && (seconds >= (FAN_end + sync[user])) )
	{
		status[user] = done;
	}

}


