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
 * @file RGB.c
 * @brief Implementation of functions in RGB.h
 *
 *  @author John Taylor 
 * 	@date Sep 18, 2019
 *      
 */
#include "RGB.h"

#ifdef FREEDOM
RGBLEDHandle RGBLED_Constructor(void *pmemory, const size_t numbytes, GPIO_Type *redBase, uint32_t redPin,
		GPIO_Type *greenBase, uint32_t greenPin,GPIO_Type *blueBase,uint32_t bluePin)
{
	RGBLEDHandle handle;
	RGBLEDObject *obj;

	if(numbytes < sizeof(RGBLEDObject))
	{
		return ((RGBLEDHandle)NULL);
	}

	handle = (RGBLEDHandle)pmemory;
	obj = (RGBLEDObject *)handle;

	obj->redPort = redBase;
	obj->redPin = redPin;

	obj->greenPort = greenBase;
	obj->greenPin = greenPin;

	obj->bluePort = blueBase;
	obj->bluePin = bluePin;

	obj->red = false;
	obj->green = false;
	obj->blue = false;

	obj->red_config.pinDirection = kGPIO_DigitalOutput;
	obj->red_config.outputLogic = 1U;
	GPIO_PinInit(obj->redPort, obj->redPin, &(obj->red_config));

	obj->green_config.pinDirection = kGPIO_DigitalOutput;
	obj->green_config.outputLogic = 1U;
	GPIO_PinInit(obj->greenPort, obj->greenPin, &(obj->green_config));

	obj->blue_config.pinDirection = kGPIO_DigitalOutput;
	obj->blue_config.outputLogic = 1U;
	GPIO_PinInit(obj->bluePort, obj->bluePin, &(obj->blue_config));
	return handle;
}
#else
RGBLEDHandle RGBLED_Constructor(void *pmemory, const size_t numbytes)
{
	RGBLEDHandle handle;
	RGBLEDObject *obj;

	if(numbytes < sizeof(RGBLEDHandle))
	{
		return ((RGBLEDHandle)NULL);
	}

	handle = (RGBLEDHandle)pmemory;
	obj = (RGBLEDObject *)handle;
	obj->red = false;
	obj->green = false;
	obj->blue = false;
	return handle;
}
#endif
void RGBLED_printStatus(RGBLEDHandle handle, bool red, bool green, bool blue)
{
	RGBLEDObject *obj = (RGBLEDObject *)handle;
	if(red)
	{
		if(obj->red)
		{
			#ifdef FREEDOM
			PRINTF("RED LED ON");
			#else
			printf("RED LED ON");
			#endif
		}
		else
		{
			#ifdef FREEDOM
			PRINTF("RED LED OFF");
			#else
			printf("RED LED OFF");
			#endif
		}
	}
	if(green)
	{
		if(obj->green)
		{
			#ifdef FREEDOM
			PRINTF("GREEN LED ON");
			#else
			printf("GREEN LED ON");
			#endif
		}
		else
		{
			#ifdef FREEDOM
			PRINTF("GREEN LED OFF");
			#else
			printf("GREEN LED OFF");
			#endif
		}
	}
	if(blue)
	{
		if(obj->blue)
		{
			#ifdef FREEDOM
			PRINTF("BLUE LED ON");
			#else
			printf("BLUE LED ON");
			#endif
		}
		else
		{
			#ifdef FREEDOM
			PRINTF("BLUE LED OFF");
			#else
			printf("BLUE LED OFF");
			#endif
		}
	}


}
void RGBLED_set(RGBLEDHandle handle, bool red, bool green, bool blue)
{
	RGBLEDObject *obj = (RGBLEDObject *)handle;

	if(!red)
	{
		obj->red = false;
		#ifdef FREEDOM
		GPIO_SetPinsOutput(obj->redPort, 1<<obj->redPin);
		#endif
		
	}
	else
	{
		#ifdef FREEDOM
		GPIO_ClearPinsOutput(obj->redPort, 1<<obj->redPin);
		#endif
		obj->red = true;
	}
	if(!blue)
	{
		#ifdef FREEDOM
		GPIO_SetPinsOutput(obj->bluePort, 1<<obj->bluePin);
		#endif
		obj->blue = false;
	}
	else
	{
		#ifdef FREEDOM
		GPIO_ClearPinsOutput(obj->bluePort,1<<obj->bluePin);
		#endif
		obj->blue = true;
	}
	if(!green)
	{
		#ifdef FREEDOM
		GPIO_SetPinsOutput(obj->greenPort,1<<obj->greenPin);
		#endif
		obj->green = false;
	}
	else
	{
		#ifdef FREEDOM
		GPIO_ClearPinsOutput(obj->greenPort, 1<< obj->greenPin);
		#endif
		obj->green = true;
	}
}


