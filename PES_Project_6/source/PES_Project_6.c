
/**
 * @file    PES_Project_6.c
 * @brief   Application entry point.
 */
#include "PES_Project_6.h"

LoggerHandle logger;

RGBLEDHandle led;

dac_config_t dacConfigStruct;

adc16_config_t adc16ConfigStruct;
adc16_channel_config_t adc16ChannelConfigStruct;


QueueHandle_t adcBuffer;
QueueHandle_t dspBuffer;
uint16_t buff[64];

dma_handle_t g_DMA_Handle;
dma_transfer_config_t transferConfig;

SemaphoreHandle_t ledMutex;
volatile bool g_Transfer_Done = false;

int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	/*
	 * setup DAC
	 */
	DAC_GetDefaultConfig(&dacConfigStruct);
	DAC_Init(DAC0, &dacConfigStruct);
	DAC_Enable(DAC0, true);             /* Enable output. */
	DAC_SetBufferReadPointer(DAC0, 0U);

	/*
	 * Setup ADC
	 */
	ADC16_GetDefaultConfig(&adc16ConfigStruct);
	ADC16_Init(DEMO_ADC16_BASE, &adc16ConfigStruct);
	ADC16_EnableHardwareTrigger(DEMO_ADC16_BASE, false); /* Make sure the software trigger is used. */
	if (kStatus_Success == ADC16_DoAutoCalibration(DEMO_ADC16_BASE))
	{
		Logger_logString(logger,"ADC16_DoAutoCalibration() Done.\r\n","main", STATUS_LEVEL);
	}
	else
	{
		Logger_logString(logger,"ADC16_DoAutoCalibration() Failed.\r\n","main", STATUS_LEVEL);
	}
	adc16ChannelConfigStruct.channelNumber = DEMO_ADC16_USER_CHANNEL;
	adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;

	//create the ADC buffer
	adcBuffer = xQueueCreate(64,sizeof(uint16_t));
	dspBuffer =  xQueueCreate(64,sizeof(uint16_t));
	if(adcBuffer != 0)
	{
		Logger_logString(logger,"ADC Queue Created Successfully\r\n","main", STATUS_LEVEL);
	}
	else
	{
		Logger_logString(logger,"Failed to create ADC Queue\r\n","main", STATUS_LEVEL);
	}

	/* Configure DMAMUX */
	DMAMUX_Init(DMAMUX0);
	DMAMUX_SetSource(DMAMUX0, DMA_CHANNEL, DMA_SOURCE);
	DMAMUX_EnableChannel(DMAMUX0, DMA_CHANNEL);

	/* Configure DMA one shot transfer */
	DMA_Init(DMA0);
	DMA_CreateHandle(&g_DMA_Handle, DMA0, DMA_CHANNEL);
	DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);


	led = malloc(sizeof(RGBLEDObject));
	led = RGBLED_Constructor((void*) led, sizeof(RGBLEDObject), RED_BASE, RED_PIN, GREEN_BASE, GREEN_PIN, BLUE_BASE, BLUE_PIN);
	RGBLED_set(led, false, false, true);
	ledMutex = xSemaphoreCreateMutex();


	logger = malloc(sizeof(LOGGERObject));
	logger = Logger_Constructor((void*)logger, sizeof(LOGGERObject));

	Logger_enable(logger);
	Logger_logString(logger, "Program Started", "main", STATUS_LEVEL);

	//calculate the sin wave in floating point representation
	float t = 0.0;
#ifdef DB
	Logger_logString(logger, "Calculating Sin Wave", "main", DEBUG_LEVEL);
#endif
	for(int i = 0; i < 50; i++)
	{
		floatWave[i] = sin(t*M_TWO_PI/PERIOD) + Y_OFFSET;

#ifdef DB
		PRINTF("X value: %f\t Y Value: %f\n\r",t,sin(t*M_TWO_PI/PERIOD) + Y_OFFSET);
#endif
		t = t + 0.1;
	}
	//convert to ADC representation
#ifdef DB
	Logger_logString(logger, "Converting to ADC representation", "main", DEBUG_LEVEL);
#endif
	for(int i = 0; i < 50; i++)
	{
		float div = (floatWave[i]/RESOLUTION);

		intWave[i] = (uint16_t)div;
#ifdef DB
		PRINTF("X value: %d\t Y Value: %d\n\r",i,intWave[i]);
#endif
	}



	xTaskCreate(updateTime,( portCHAR *)"update_time", configMINIMAL_STACK_SIZE, NULL, 3, NULL);

	xTaskCreate(updateDAC,( portCHAR *)"update_dac", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

#ifdef APPLICATION
	xTaskCreate(readADC,( portCHAR *)"read_adc", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
#endif
	vTaskStartScheduler();

	while(1)
	{

	}
}


void DMA_Callback(dma_handle_t *handle, void *param)
{
    g_Transfer_Done = true;
}
