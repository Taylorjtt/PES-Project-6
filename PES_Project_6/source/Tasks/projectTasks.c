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
uint16_t minInt;
uint16_t maxInt;
uint32_t sum;
uint32_t stdDevSum;
float values[64];
float min;
float max;
float average;
float std_dev;
uint16_t current;
uint8_t cycle = 0;
TaskHandle_t dspTaskHandle;
uint8_t adcReadCount;
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
		if(ledMutex != NULL)
		{
			if(xSemaphoreTake(ledMutex,(TickType_t) 100) == pdTRUE)
			{
				RGBLED_set(led, false, !RGBLED_isGreenOn(led),false );
				xSemaphoreGive( ledMutex );
			}
		}

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
		adcReadCount++;
		if(adcReadCount > 4)
		{
			xSemaphoreGive( ledMutex );
		}
        ADC16_SetChannelConfig(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP, &adc16ChannelConfigStruct);
        while (0U == (kADC16_ChannelConversionDoneFlag &
                      ADC16_GetChannelStatusFlags(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP)))
        {
        }
        uint16_t value = ADC16_GetChannelConversionValue(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP);


        if(!(xQueueSend(adcBuffer,(void *)&value,0) == pdTRUE))
        {
        	adcReadCount = 0;
        	xSemaphoreTake(ledMutex,(TickType_t) 100);
        	RGBLED_set(led, false, false,true);
        	Logger_logString(logger, "Queue is Full", "readADC", STATUS_LEVEL);
        	DMA_PrepareTransfer(&transferConfig,adcBuffer->pcHead,2,buff,2,64*2,
        				kDMA_MemoryToMemory);
        	DMA_SubmitTransfer(&g_DMA_Handle, &transferConfig, kDMA_EnableInterrupt);
        	DMA_StartTransfer(&g_DMA_Handle);
        	Logger_logString(logger, "DMA Xfer Started", "readADC", DEBUG_LEVEL);
            while (g_Transfer_Done != true)
            {
            }
            Logger_logString(logger, "DMA Xfer complete", "readADC", DEBUG_LEVEL);
            xQueueReset(adcBuffer);

            xTaskCreate(doDSP,( portCHAR *)"doDSP", configMINIMAL_STACK_SIZE, NULL, 1, &dspTaskHandle);

        }

		vTaskDelay(100);
	}

}

void doDSP(void *p)
{
	while(true)
	{
		minInt = 65535;
		maxInt = 0;
		sum = 0;
		stdDevSum = 0;
		for(int i = 0; i < 64; i++)
		{
	    	if(buff[i] > maxInt)
	    	{
	    		maxInt = buff[i] ;
	    	}
	    	if(buff[i]  < minInt)
	    	{
	    		minInt = buff[i] ;
	    	}
	    	values[i] = buff[i] *RESOLUTION;
	    	sum+=buff[i];
		}

	    min = minInt*RESOLUTION;
	    max = maxInt*RESOLUTION;
	    average = sum*RESOLUTION/64.0;
	    float stdDevSum = 0.0f;
	    for(int j = 0; j < 64; j++)
	    {
	    	stdDevSum += powf((values[j] - average), 2);
	    }
	    std_dev = sqrtf(stdDevSum/64.0);
	    Logger_logString(logger, "DSP REPORT", "doDSP", STATUS_LEVEL);
	    PRINTF("Cycle Number: %d\n\r",cycle);
	    PRINTF("Min: %f\n\rMax: %f\n\rAvg: %f\n\rStd Dev: %f\n\r",min,max,average,std_dev);
	    cycle++;
	    if(cycle > 4)
	    {
	    	vTaskEndScheduler();
	    }
	    vTaskSuspend( NULL );
	}

}
