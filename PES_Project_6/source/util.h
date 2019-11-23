/*
 * util.h
 *
 *  Created on: Nov 1, 2019
 *      Author: john
 */

#ifndef UTIL_H_
#define UTIL_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
typedef struct timestamp
{
	uint32_t hours;
	uint32_t minutes;
	uint32_t seconds;
	uint32_t tenths;
}timestamp;

extern volatile timestamp time;

#define EnableInterrupts asm(" CPSIE i");
#define DisableInterrupts asm(" CPSID i");
#define START_CRITICAL DisableInterrupts
#define END_CRITICAL EnableInterrupts
extern uint32_t usecs;
void updateTime(volatile timestamp* ts);
void delayMilliseconds(uint32_t delay);
#endif /* UTIL_H_ */
