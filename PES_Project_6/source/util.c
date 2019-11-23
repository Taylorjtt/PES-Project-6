/*
 * util.h
 *
 *  Created on: Nov 1, 2019
 *      Author: john
 */
#include "util.h"
uint32_t usecs = 0U;
volatile timestamp time=
{
	.tenths = 0,.seconds = 0, .minutes = 0, .hours = 0
};
void delayMilliseconds(uint32_t delay)
{
	uint32_t entryTime = usecs;
	while((usecs - entryTime) < delay*1000);
}

void updateTime(volatile timestamp* ts)
{
	ts->tenths++;
	if(ts->tenths >10)
	{
		ts->tenths = 0;
		ts->seconds++;
		if(ts->seconds > 60)
		{
			ts->seconds = 0;
			ts->minutes++;

			if(ts->minutes > 60)
			{
				ts->minutes = 0;
				ts->hours++;
			}
		}
	}
}

