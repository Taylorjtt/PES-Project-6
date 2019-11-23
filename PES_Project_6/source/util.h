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




#define EnableInterrupts asm(" CPSIE i");
#define DisableInterrupts asm(" CPSID i");
#define START_CRITICAL DisableInterrupts
#define END_CRITICAL EnableInterrupts
extern uint32_t usecs;

void delayMilliseconds(uint32_t delay);
#endif /* UTIL_H_ */
