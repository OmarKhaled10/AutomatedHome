/*
 * Test_Main.c
 *
 * Created: 4/20/2021 9:26:00 PM
 *  Author: lenovo
 */

/*
 * main.c
 *
 *  Created on: Apr 22, 2021
 *      Author: OMAR
 */
#include <stdint.h>
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "lcd.h"
#include "KEYBAD.h"
#include "external_eeprom.h"
#include "spi.h"
#include "mfrc522.h"
#include "Servo.h"
#include "routine1.h"
#define PA (uint8)0


void Timer_Init(void);
void USER(uint8 user,uint16 adress);
uint8 USER_OPTIONS(void);
uint8 MASTER_OPTIONS(void);
uint8 IF_MASTER(uint8 id);
uint8 IF_FOUND(uint8 id,uint16 *add);
uint16 CHECK_EMPTY(void);
void DELETE(uint16 adress);
void CARD(void);
void take_Routine(uint16 address);

#define prestart  192

uint16 TK = 0;

uint16 seconds = 0;

uint8_t str[MAX_LEN];
uint8_t byte;
uint8 mode=0;
uint8 arr1[3]={0,0,0};

int main() {

	MCUCSR |= (1<<JTD);
	MCUCSR |= (1<<JTD);
	CLEAR_BIT(DDRD,2);
	SET_BIT(PORTD,2);
	SET_BIT(DDRD,0);
	SET_BIT(DDRD,1);
	SET_BIT(DDRD,3);
	SET_BIT(DDRD,4);
	SET_BIT(DDRD,6);
	SET_BIT(DDRD,7);
	SET_BIT(DDRC,2);
	SET_BIT(DDRC,3);
	SET_BIT(DDRB,3);
	SET_BIT(PORTD,1);
	SET_BIT(PORTD,6);
	SET_BIT(PORTD,7);
	MCUCR =0x00;
	GICR =0x40;
	sei();
	_delay_ms(50);
	KEY_vidInit(PA);
	Timer_Init();
	EEPROM_init();
	LCD_init();
	Ser_vidInti();

	spi_init();

	_delay_ms(5);

	//init reader
	mfrc522_reset();
	mfrc522_init();

	//check version of the reader
	byte = mfrc522_read(VersionReg);

	//LCD_displayCharacter(byte);
	_delay_ms(50);
	LCD_clearScreen();
	if (byte == 0x92) {
		LCD_displayStringRowColumn(0, 0, "MIFARE RC522v2");
		LCD_displayStringRowColumn(1, 0, "Detected");
	} else if (byte == 0x91 || byte == 0x90) {
		LCD_displayStringRowColumn(0, 0, "MIFARE RC522v1");
		LCD_displayStringRowColumn(1, 0, "Detected");
	} else {
		LCD_displayStringRowColumn(0, 0, "No reader found");
	}

	while (1) {
		for(uint8 i=0;i<4;i++)
		{
			if(arr1[i]==1){USER(1,0);}
			else if(arr1[i]==2){USER(2,14);}
			else if(arr1[i]==3){USER(3,28);}
		}

	}
	return 0;
}



ISR(INT0_vect) {
	CARD();
	uint8 IDs,PW,EEPROM_PW;
	uint8 wrong=0;
	if(str[0]==103)
	{
		//master
		LCD_clearScreen();
		LCD_displayString("Enter the P.W:");
		uint8 j=0;
		for(uint16 i=0;i<4;i++)
		{	PW=0xff;
		while(PW==0xff){
			PW=KEY_u8GetButton();
		}
		//				EEPROM_readByte(0x0001+i,&EEPROM_PW);
		LCD_goToRowColumn(1,0+i);
		LCD_intgerToString(PW);
		if(PW==i)////////////////////////////////////
		{j++;}
		}
		if(j==4)
		{
			LCD_clearScreen();
			LCD_displayString("Correct PW");
			wrong=2;
			//master mode
			uint8 Moption;
			Moption=MASTER_OPTIONS();
			if(Moption==1)
			{
				//add
				CARD();
				uint8 checkM=IF_MASTER(str[0]);
				uint16 add;
				uint8 found=IF_FOUND(str[0],&add);
				uint16 Eadd=CHECK_EMPTY();
				if((checkM==0)&&(found==0)&&(Eadd!=0xffff))
				{	EEPROM_writeByte(Eadd,str[0]);
				_delay_ms(50);
				LCD_goToRowColumn(1,0);
				EEPROM_readByte(Eadd,&checkM);
				LCD_clearScreen();
				LCD_intgerToString(checkM);
				take_Routine(Eadd);
				LCD_clearScreen();
				LCD_displayString("ADD success");
				}else
				{
					LCD_clearScreen();
					LCD_displayString("ADD fail");
					_delay_ms(100);
				}

			}else if(Moption==2)
			{
				//delete
				CARD();
				uint8 checkM=IF_MASTER(str[0]);
				uint16 add;
				uint8 found=IF_FOUND(str[0],&add);
				if((checkM==0)&&(found==1))
				{
					DELETE(add);
					LCD_clearScreen();
					LCD_displayString("DELETE success");
				}else
				{
					LCD_clearScreen();
					LCD_displayString("DELETE fail");
				}


			}
		}else
		{
			LCD_clearScreen();
			LCD_displayString("Wrong PW");
			wrong=1;
		}
	}if(wrong==0)
	{ uint16 adress;
	uint8 user=0;
	for(uint16 k=0;k<29;k+=14)
	{adress=0+k;
	user++;
	EEPROM_readByte(adress,&IDs);///////////////////
	_delay_ms(50);
	if(str[0]==IDs)
	{
		Clear_Routine_Flags(user);
		//User mode
		mode=user;
		uint8 l=0;
		for(uint8 m=0;m<4;m++)
		{
			if(arr1[m]==0)
			{
				for(uint8 n=0;n<4;n++)
				{
					if(arr1[n]==user)
					{
						l=1;
						break;
					}
				}
				if(l==0)
				{
					arr1[m]=user;
				}
			}
		}
		uint8 Uoption;
		Ser_vidState(OPEN);
		Uoption=USER_OPTIONS();
		switch(mode)
		{

		case 1:
		{

			//user1

			if(Uoption==1)
			{
				USER(1,0);
			}else if(Uoption==2)
			{
				take_Routine(0);
			}
			_delay_ms(500);
			Ser_vidState(CLOSE);
			break;
		}
		case 2:
		{
			//user2

			if(Uoption==1)
			{
				USER(2,14);
			}else if(Uoption==2)
			{
				take_Routine(14);
			}
			_delay_ms(500);
			Ser_vidState(CLOSE);
			break;
		}
		case 3:
		{
			//user3

			if(Uoption==1)
			{
				USER(3,28);
			}else if(Uoption==2)
			{
				take_Routine(28);
			}
			_delay_ms(500);
			Ser_vidState(CLOSE);
			break;
		}

		}
	}
	}
	}

}

ISR(TIMER0_OVF_vect)
{
	TK++;

	if(TK == 3907)
	{
		TCNT0 = prestart;
		TK = 0;
		seconds++;
		//for testing start
		TOGGLE_BIT(PORTA,3);
		//for testing end
	}
}


void Timer_Init(void)
{
	__asm__("SEI");  		 //enable all interrupts
	TIMSK |= (1<<TOIE0);     //enable timer0 interrupt

	TCNT0 = prestart;		 //set the TCNT0 register with starting value 192 (some math)
	TCCR0 |= (1<<CS01);      //starting timer0 with prescaler 8
}

void USER (uint8 user,uint16 adress)
{
	uint8 LED1_enable,LED1_start,LED1_end;
	uint8 LED2_enable,LED2_start,LED2_end;
	uint8 FAN_enable,FAN_start,FAN_end;
	EEPROM_readByte(adress+5,&LED1_enable);
	_delay_ms(10);
	EEPROM_readByte(adress+6,&LED1_start);
	_delay_ms(10);
	EEPROM_readByte(adress+7,&LED1_end);
	_delay_ms(10);
	EEPROM_readByte(adress+8,&LED2_enable);
	_delay_ms(10);
	EEPROM_readByte(adress+9,&LED2_start);
	_delay_ms(10);
	EEPROM_readByte(adress+10,&LED2_end);
	_delay_ms(10);
	EEPROM_readByte(adress+11,&FAN_enable);
	_delay_ms(10);
	EEPROM_readByte(adress+12,&FAN_start);
	_delay_ms(10);
	EEPROM_readByte(adress+13,&FAN_end);
	_delay_ms(10);
	Do_Routine(seconds,user,LED1_enable ,LED1_start ,LED1_end ,LED2_enable ,LED2_start ,LED2_end ,FAN_enable ,FAN_start ,FAN_end);

}

uint8 USER_OPTIONS(void)
{
	uint8 PW;
	LCD_clearScreen();
	LCD_displayString("DO= 1  EDIT= 2");
	PW=0xff;
	while((PW==0xff)&&((PW!=2)||(PW!=1))){
		PW=KEY_u8GetButton();
	}
	LCD_goToRowColumn(1,0);
	LCD_intgerToString(PW);
	_delay_ms(50);
	return PW;
}

uint8 MASTER_OPTIONS(void)
{
	uint8 PW;
	LCD_clearScreen();
	LCD_displayString("ADD= 1  DEL= 2");
	PW=0xff;
	while((PW==0xff)&&((PW!=2)||(PW!=1))){
		PW=KEY_u8GetButton();
	}
	LCD_goToRowColumn(1,0);
	LCD_intgerToString(PW);
	_delay_ms(50);
	return PW;
}

uint8 IF_MASTER(uint8 id)
{
	if(id==103){return 1;}
	else{return 0;}
}

uint8 IF_FOUND(uint8 id,uint16* add)
{uint16 adress;
uint8 H,flag=0;
for(uint16 i=0;i<29;i+=14)
{
	adress=0+i;
	EEPROM_readByte(adress,&H);
	_delay_ms(10);
	if(id==H){flag=1;
	*add=adress;
	break;}
}
if(flag==1){return 1;}
else{return 0;}
}

uint16 CHECK_EMPTY(void)
{
	uint16 adress;
	uint8 H,flag=0;
	for(uint16 i=0;i<29;i+=14)
	{
		adress=0+i;
		EEPROM_readByte(adress,&H);
		_delay_ms(50);
		if(0==H){flag=1;
		return adress;
		break;}
	}
	if(flag==0){return 0xffff;}
}

void DELETE(uint16 adress)
{
	for(uint16 i=0;i<14;i++)
	{
		EEPROM_writeByte(adress+i,0);
		_delay_ms(10);
	}
}

void CARD(void)
{
	LCD_clearScreen();
	LCD_displayString("Show Your Card");

	while ((mfrc522_request(PICC_REQALL, str) != CARD_FOUND)) {
		mfrc522_init();
		byte = mfrc522_read(ComIEnReg);
		mfrc522_write(ComIEnReg, byte | 0x20);
		byte = mfrc522_read(DivIEnReg);
		mfrc522_write(DivIEnReg, byte | 0x80);
	}

	if (mfrc522_get_card_serial(str) == CARD_FOUND)

	{
		//EEPROM_writeByte(0x0000,str[0]);
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "Card Found");
		LCD_goToRowColumn(1, 0);
		uint8_t i = 0;
		for (; i < 4; i++) {

			LCD_intgerToString(str[i]);
			if (i != 3) {
				LCD_displayCharacter('.');
			}

		}
		//		LCD_intgerToString(str[0]);
		_delay_ms(500);
		LCD_clearScreen();
	}

}
void take_Routine(uint16 address)
{

	uint8 key1;
	uint8 key2;
	uint8 key;
	uint8 confirmation;
	uint8 start;
	uint8 end;
	uint8 temp=0xff;

	/*********************************************************/
	/***********************LED0*****************************/
	/*******************************************************/

	//LED0 MODE

	LCD_displayString("LED0 on=1, off=0");
	while((temp!=0)&&(temp!=1))
	{
		temp=KEY_u8GetButton();
	}
	LCD_goToRowColumn(1,0);
	LCD_intgerToString(temp);
	EEPROM_writeByte((address+5),temp);
	temp=0xff;
	_delay_ms(250);
	LCD_clearScreen();

	//LED0 START TIME
	LCD_displayString("Enter start time");
	LCD_goToRowColumn(1,0);
	key1=0xff;
	while(key1==0xff){
		key1 = KEY_u8GetButton();}
	LCD_intgerToString(key1);
	LCD_goToRowColumn(1,1);
	key2=0xff;
	while(key2==0xff){
		key2 = KEY_u8GetButton();}
	LCD_intgerToString(key2);

	key = (key1*10) + key2;
	start = key;
	_delay_ms(250);
	LCD_clearScreen();

	do
	{
		LCD_clearScreen();
		LCD_displayString("Hit Equal");
		confirmation = KEY_u8GetButton();
	}
	while(confirmation != '*');

	LCD_clearScreen();

	LCD_displayString("Start time is: ");
	LCD_goToRowColumn(1,0);
	LCD_intgerToString(key);
	EEPROM_writeByte((address + 6), key);
	_delay_ms(250);
	LCD_clearScreen();

	//LED0 END TIME
	LCD_displayString("Enter end time");
	LCD_goToRowColumn(1,0);
	key1=0xff;
	while(key1==0xff){
		key1 = KEY_u8GetButton();}
	LCD_intgerToString(key1);
	LCD_goToRowColumn(1,1);
	key2=0xff;
	while(key2==0xff){
		key2 = KEY_u8GetButton();}
	LCD_intgerToString(key2);

	key = (key1*10) + key2;
	end = key;
	_delay_ms(250);
	LCD_clearScreen();

	do
	{
		LCD_clearScreen();
		LCD_displayString("Hit Equal");
		confirmation = KEY_u8GetButton();
	}
	while(confirmation != '*');

	LCD_clearScreen();

	LCD_displayString("End time is: ");
	LCD_goToRowColumn(1,0);
	LCD_intgerToString(key);
	EEPROM_writeByte((address + 7), key);
	_delay_ms(250);
	LCD_clearScreen();

	/*********************************************************/
	/***********************LED1*****************************/
	/*******************************************************/

	//LED1 MODE

	LCD_displayString("LED1 on=1, off=0");
	while((temp!=0)&&(temp!=1))
	{
		temp=KEY_u8GetButton();
	}
	LCD_goToRowColumn(1,0);
	LCD_intgerToString(temp);
	EEPROM_writeByte((address+8),temp);
	temp=0xff;
	_delay_ms(250);
	LCD_clearScreen();

	//LED1 START TIME
	LCD_displayString("Enter start time");
	LCD_goToRowColumn(1,0);
	key1=0xff;
	while(key1==0xff){
		key1 = KEY_u8GetButton();}
	LCD_intgerToString(key1);
	LCD_goToRowColumn(1,1);
	key2=0xff;
	while(key2==0xff){
		key2 = KEY_u8GetButton();}
	LCD_intgerToString(key2);

	key = (key1*10) + key2;
	start = key;
	_delay_ms(250);
	LCD_clearScreen();

	do
	{
		LCD_clearScreen();
		LCD_displayString("Hit Equal");
		confirmation = KEY_u8GetButton();
	}
	while(confirmation != '*');

	LCD_clearScreen();

	LCD_displayString("Start time is: ");
	LCD_goToRowColumn(1,0);
	LCD_intgerToString(key);
	EEPROM_writeByte((address + 9), key);
	_delay_ms(250);
	LCD_clearScreen();

	//LED1 END TIME
	LCD_displayString("Enter end time");
	LCD_goToRowColumn(1,0);
	key1=0xff;
	while(key1==0xff){
		key1 = KEY_u8GetButton();}
	LCD_intgerToString(key1);
	LCD_goToRowColumn(1,1);
	key2=0xff;
	while(key2==0xff){
		key2 = KEY_u8GetButton();}
	LCD_intgerToString(key2);
	key = (key1*10) + key2;
	end = key;
	_delay_ms(250);
	LCD_clearScreen();

	do
	{
		LCD_clearScreen();
		LCD_displayString("Hit Equal");
		confirmation = KEY_u8GetButton();
	}
	while(confirmation != '*');

	LCD_clearScreen();

	LCD_displayString("End time is: ");
	LCD_goToRowColumn(1,0);
	LCD_intgerToString(key);
	EEPROM_writeByte((address + 10), key);
	_delay_ms(250);
	LCD_clearScreen();

	/*********************************************************/
	/***********************FAN******************************/
	/*******************************************************/

	//FAN MODE

	LCD_displayString("FAN on=1, off=0");
	while((temp!=0)&&(temp!=1))
	{
		temp=KEY_u8GetButton();
	}
	LCD_goToRowColumn(1,0);
	LCD_intgerToString(temp);
	EEPROM_writeByte((address+11),temp);
	temp=0xff;
	_delay_ms(250);
	LCD_clearScreen();

	//FAN START TIME
	LCD_displayString("Enter start time");
	LCD_goToRowColumn(1,0);
	key1=0xff;
	while(key1==0xff){
		key1 = KEY_u8GetButton();}
	LCD_intgerToString(key1);
	LCD_goToRowColumn(1,1);
	key2=0xff;
	while(key2==0xff){
		key2 = KEY_u8GetButton();}
	LCD_intgerToString(key2);
	key = (key1*10) + key2;
	start = key;
	_delay_ms(250);
	LCD_clearScreen();

	do
	{
		LCD_clearScreen();
		LCD_displayString("Hit Equal");
		confirmation = KEY_u8GetButton();
	}
	while(confirmation != '*');

	LCD_clearScreen();

	LCD_displayString("Start time is: ");
	LCD_goToRowColumn(1,0);
	LCD_intgerToString(key);
	EEPROM_writeByte((address + 12), key);
	_delay_ms(250);
	LCD_clearScreen();

	//FAN END TIME
	LCD_displayString("Enter end time");
	LCD_goToRowColumn(1,0);
	key1=0xff;
	while(key1==0xff){
		key1 = KEY_u8GetButton();}
	LCD_intgerToString(key1);
	LCD_goToRowColumn(1,1);
	key2=0xff;
	while(key2==0xff){
		key2 = KEY_u8GetButton();}
	LCD_intgerToString(key2);
	key = (key1*10) + key2;
	end = key;
	_delay_ms(250);
	LCD_clearScreen();

	do
	{
		LCD_clearScreen();
		LCD_displayString("Hit Equal");
		confirmation = KEY_u8GetButton();
	}
	while(confirmation != '*');

	LCD_clearScreen();

	LCD_displayString("End time is: ");
	LCD_goToRowColumn(1,0);
	LCD_intgerToString(key);
	EEPROM_writeByte((address + 13), key);
	_delay_ms(250);
	LCD_clearScreen();
}
