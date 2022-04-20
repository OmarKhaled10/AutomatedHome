/*
 * Utils.h
 *
 *  Created on: Apr 10, 2021
 *      Author: OMAR
 */

#ifndef UTILS_H_
#define UTILS_H_

#define SetBit(reg,bit) reg|=(1<<bit)
#define ClrBit(reg,bit) reg&=(~(1<<bit))
#define ToggleBit(reg,bit) reg^=(1<<bit)
#define GetBit(reg,bit) ((reg>>bit)&1)

#endif /* UTILS_H_ */
