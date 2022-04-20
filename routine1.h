/*
 * routine.h
 *
 *  Created on: Apr 27, 2021
 *      Author: OMAR
 */

#ifndef ROUTINE_H_
#define ROUTINE_H_

#define onit 	1
#define done 	2
#define all		4

#define LED1_user1_port		PORTC
#define LED2_user1_port		PORTC
#define FAN_user1_port		PORTD
#define LED1_user1_pin		3
#define LED2_user1_pin		2
#define FAN_user1_pin		7

#define LED1_user2_port		PORTB
#define LED2_user2_port		PORTD
#define FAN_user2_port		PORTD
#define LED1_user2_pin		3
#define LED2_user2_pin		0
#define FAN_user2_pin		1

#define LED1_user3_port		PORTD
#define LED2_user3_port		PORTD
#define FAN_user3_port		PORTD
#define LED1_user3_pin		3
#define LED2_user3_pin		4
#define FAN_user3_pin		6

extern void Do_Routine(uint8 seconds , uint8 user, uint8 LED1_enable , uint8 LED1_start , uint8 LED1_end , uint8 LED2_enable , uint8 LED2_start , uint8 LED2_end , uint8 FAN_enable , uint8 FAN_start , uint8 FAN_end);
extern void Clear_Routine_Flags(uint8 user);
extern uint8 Get_status(uint8 user);


#endif /* ROUTINE_H_ */
