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
		vTaskDelay(100);
	}
}

void updateDAC(void *p)
{
	while(true)
	{
#ifdef APPLICATION
		RGBLED_set(led, false, !RGBLED_isGreenOn(led),false );
#else
		RGBLED_set(led, false, false, !RGBLED_isBlueOn(led));
#endif
		DAC_SetBufferValue(DAC0, 0U, intWave[i++]);
		if(i > 49)
		{
			i = 0;
		}
		#ifdef DB
		Logger_logString(logger, "Updating DAC", "updateDAC", DEBUG_LEVEL);
		PRINTF("X Value: %d\tY Value: %d\n\r",i,intWave[i - 1]);
		#endif
		vTaskDelay(100);
	}

}

void readADC(void *p)
{
	while(true)
	{
        ADC16_SetChannelConfig(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP, &adc16ChannelConfigStruct);
        while (0U == (kADC16_ChannelConversionDoneFlag &
                      ADC16_GetChannelStatusFlags(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP)))
        {
        }
        uint16_t value = ADC16_GetChannelConversionValue(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP);

        if(!xQueueSend(adcBuffer,(void *)&value,0) == pdTRUE)
        {
        	Logger_logString(logger, "Queue is Full", "readADC", STATUS_LEVEL);
        }

		vTaskDelay(100);
	}

}
