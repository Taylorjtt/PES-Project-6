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
 * @file PES_Project_6.h
 * @brief
 *
 *  @author John Taylor
 * 	@date Nov 22, 2019
 *
 */
#ifndef PES_PROJECT_6_H_
#define PES_PROJECT_6_H_

#include <stdio.h>
#include "mode.h"
#include "util.h"
#include <stdlib.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "LED/RGB.h"
#include "Logger/logger.h"
#include <math.h>
#include <Tasks/projectTasks.h>
#include "fsl_dac.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "fsl_adc16.h"
#include "fsl_dma.h"
#include "fsl_dmamux.h"
#include "freertos/semphr.h"


#define RED_BASE GPIOB
#define RED_PIN 18U

#define GREEN_BASE GPIOB
#define GREEN_PIN 19U

#define BLUE_BASE GPIOD
#define BLUE_PIN 1U

#define RESOLUTION (3.3/4096)

#define M_PI 3.14159265358979323846
#define M_TWO_PI (2*M_PI)
#define PERIOD 5.0f
#define Y_OFFSET 2.0f

#define DEMO_ADC16_BASE ADC0
#define DEMO_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_USER_CHANNEL 8u /*PTB0, ADC0_SE8 */

#define BUFF_LENGTH 64
#define DMA_CHANNEL 0
#define DMA_SOURCE 63

extern float floatWave[50];
extern uint16_t intWave[50];

extern LoggerHandle logger;
extern RGBLEDHandle led;

extern adc16_config_t adc16ConfigStruct;
extern adc16_channel_config_t adc16ChannelConfigStruct;

extern QueueHandle_t adcBuffer;
extern QueueHandle_t dspBuffer;
extern uint16_t buff[64];
extern dma_handle_t g_DMA_Handle;
extern dma_transfer_config_t transferConfig;
extern SemaphoreHandle_t ledMutex;
void DMA_Callback(dma_handle_t *handle, void *param);
extern volatile bool g_Transfer_Done;
#endif /* PES_PROJECT_6_H_ */
