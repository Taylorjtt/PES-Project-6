 
/**
 * @file    PES_Project_6.c
 * @brief   Application entry point.
 */
#include "PES_Project_6.h"

LoggerHandle logger;
RGBLEDHandle led;

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    dac_config_t dacConfigStruct;
    DAC_GetDefaultConfig(&dacConfigStruct);
    DAC_Init(DAC0, &dacConfigStruct);
    DAC_Enable(DAC0, true);             /* Enable output. */
    DAC_SetBufferReadPointer(DAC0, 0U);

	//10hz
	SysTick_Config(4800000);

	led = malloc(sizeof(RGBLEDObject));
	led = RGBLED_Constructor((void*) led, sizeof(RGBLEDObject), RED_BASE, RED_PIN, GREEN_BASE, GREEN_PIN, BLUE_BASE, BLUE_PIN);
	RGBLED_set(led, false, false, true);



	logger = malloc(sizeof(LOGGERObject));
	logger = Logger_Constructor((void*)logger, sizeof(LOGGERObject));

	Logger_enable(logger);
	Logger_logString(logger, "Program Started", "main", STATUS_LEVEL);

	//calculate the sin wave in floating point representation
	float t = 0.0;
	for(int i = 0; i < 50; i++)
	{
		floatWave[i] = sin(t*M_TWO_PI/PERIOD) + Y_OFFSET;
		t = t + 0.1;
	}
	//convert to ADC representation
	for(int i = 0; i < 50; i++)
	{
		float div = (floatWave[i]/RESOLUTION);
		intWave[i] = (uint16_t)div;
	}



	xTaskCreate(updateTime,(signed portCHAR *)"update_time", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(updateDAC,(signed portCHAR *)"update_dac", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();
	while(1)
	{

	}
}
