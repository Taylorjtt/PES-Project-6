/*****************************************************************************
* Copyright (C) 2019 by John Taylor
*
* Redistribution, modification or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. Users are
* permitted to modify this and use it to learn about the field of embedded
* software. John Taylor and the University of Colorado are not liable for
* any misuse of this material.
*
*****************************************************************************/
/*
 * @file tasks.c
 * @brief
 *
 *  @author John Taylor
 * 	@date Nov 22, 2019
 *
 */
#include <Tasks/projectTasks.h>
float floatWave[50];
uint16_t intWave[50];
uint8_t i = 0;
timestamp time=
{
	.tenths = 0,.seconds = 0, .minutes = 0, .hours = 0
};
void updateTime(void *p)
{
	while(1)
	{
		time.tenths++;
		if(time.tenths >=10)
		{
			time.tenths = 0;
			time.seconds++;
			if(time.seconds >= 60)
			{
				time.seconds = 0;
				time.minutes++;

				if(time.minutes >= 60)
				{
					time.minutes = 0;
					time.hours++;
				}
			}
		}
		PRINTF("%d:%d:%d.%d\n\r",time.hours,time.minutes,time.seconds,time.tenths);
		vTaskDelay(100);
	}
}

void updateDAC(void *p)
{
	while(true)
	{
		DAC_SetBufferValue(DAC0, 0U, intWave[i++]);
		if(i > 49)
		{
			i = 0;
		}
		vTaskDelay(100);
	}

}
