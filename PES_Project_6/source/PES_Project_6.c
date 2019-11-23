 
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

	//10hz
	SysTick_Config(4800000);

	led = malloc(sizeof(RGBLEDObject));
	led = RGBLED_Constructor((void*) led, sizeof(RGBLEDObject), RED_BASE, RED_PIN, GREEN_BASE, GREEN_PIN, BLUE_BASE, BLUE_PIN);
	RGBLED_set(led, false, false, true);



	logger = malloc(sizeof(LOGGERObject));
	logger = Logger_Constructor((void*)logger, sizeof(LOGGERObject));

	Logger_enable(logger);
	Logger_logString(logger, "Program Started", "main", STATUS_LEVEL);



}
