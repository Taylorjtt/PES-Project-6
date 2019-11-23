/*
 * util.h
 *
 *  Created on: Nov 1, 2019
 *      Author: john
 */
#include "util.h"
uint32_t usecs = 0U;

void delayMilliseconds(uint32_t delay)
{
	uint32_t entryTime = usecs;
	while((usecs - entryTime) < delay*1000);
}



