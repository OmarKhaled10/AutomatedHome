 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: OMAR
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_



/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif


/* LCD HW Pins */
#define RS 0
#define RW 1
#define E  2
#define LCD_CTRL_PORT PORTB
#define LCD_CTRL_PORT_DIR DDRB

#define LCD_DATA_PORT PORTC
#define LCD_DATA_PORT_DIR DDRC

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80 

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
extern void LCD_sendCommand(uint8_t command);
extern void LCD_displayCharacter(uint8_t data);
extern void LCD_displayString(const char *Str);
extern void LCD_init(void);
extern void LCD_clearScreen(void);
extern void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const char *Str);
extern void LCD_goToRowColumn(uint8_t row,uint8_t col);
extern void LCD_intgerToString(int data);

#endif /* LCD_H_ */
