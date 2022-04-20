/*
 * DIO.h
 *
 *  Created on: Apr 10, 2021
 *      Author: OMAR
 */

#ifndef DIO_H_
#define DIO_H_

/****************************************************************/
/*********************MACROS************************************/
/**************************************************************/
#define PA (uint8)0
#define PB (uint8)1
#define PC (uint8)2
#define PD (uint8)3
/*------------------------------------*/
#define OUTPUT (uint8)0
#define INFREE (uint8)1
#define INPULLUP (uint8)2
/*------------------------------------*/
#define HIGH (uint8)1
#define LOW (uint8)0

/***************************************************************/
/************************FUNCTIONS******************************/
/**************************************************************/
extern void DIO_vidSetPinDir (uint8 u8port_no,uint8 u8pin_no,uint8 u8dir);
extern void DIO_vidSetPortDir (uint8 u8port_no,uint8 u8dir);
extern void DIO_vidWriteOnPin (uint8 u8port_no,uint8 u8pin_no,uint8 u8level);
extern void DIO_vidWrireOnPort (uint8 u8port_no,uint8 u8data);
extern uint8 DIO_u8ReadFromPin (uint8 u8port_no,uint8 u8pin_no);
extern uint8 DIO_u8ReadFromPort (uint8 u8Port_no);

#endif /* DIO_H_ */
