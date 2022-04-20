/*
 * spi.h
 *
 *  Created on: Apr 22, 2021
 *      Author: OMAR
 */

#ifndef SPI_H_
#define SPI_H_

/*
 * Set to 1, spi api will work in master mode
 * else in slave mode
 */
#define SPI_CONFIG_AS_MASTER 	1


/*
 * Config SPI pin diagram
 */
#define SPI_DDR		DDRB
#define SPI_PORT	PORTB
#define SPI_PIN		PINB
#define SPI_MOSI	PB5
#define SPI_MISO	PB6
#define SPI_SS		PB4
#define SPI_SCK		PB7

void spi_init(void);                        // spi.c line 8
uint8_t spi_transmit(uint8_t data);     // spi.c line 15

#define ENABLE_CHIP() (SPI_PORT &= (~(1<<SPI_SS)))
#define DISABLE_CHIP() (SPI_PORT |= (1<<SPI_SS))

#endif /* SPI_H_ */
