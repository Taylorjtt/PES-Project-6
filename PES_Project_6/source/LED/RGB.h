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
 * @file RGB.h
 * @brief A class file for an RGB LED
 *
 *  @author John Taylor 
 * 	@date Sep 18, 2019
 *      
 */

#ifndef SRC_LED_RGB_H_
#define SRC_LED_RGB_H_
#define FREEDOM
#include <stdbool.h>
#include <stdint.h>
#ifdef FREEDOM
	#include "../../CMSIS/MKL25Z4.h"
	#include "../../drivers/fsl_gpio.h"
	#include "fsl_debug_console.h"
#else
	#include <stdio.h>
#endif

/**
* @brief Structure representing an RGB LED object
*
*/
typedef struct RGB_LED_OBJ
{
	//gpio pins
	uint32_t redPin;
	uint32_t greenPin;
	uint32_t bluePin;

	#ifdef FREEDOM
	//ports
	GPIO_Type *redPort;
	GPIO_Type *greenPort;
	GPIO_Type *bluePort;

	//pin configuration structs
	gpio_pin_config_t red_config;
	gpio_pin_config_t green_config;
	gpio_pin_config_t blue_config;
	#endif

	//keep track of which LEDS are on
	bool red;
	bool green;
	bool blue;

}RGBLEDObject;

//typedef for a pointer to an RGB_LED_OBJ named RGBLEDHandle
typedef struct RGB_LED_OBJ *RGBLEDHandle;

/**
* @brief Constructor for RGB LED object
*
* Given a chunk of memory, the size of an RGB_LED object, GPIO Ports and Pins this function
* initializes the GPIO to be used as an RGB LED and returns a pointer to the object
*
* @param pmemory	The pointer to the memory that this object will use
* @param numbytes	The expected size of the object
*
* @param redPort	The Red LED Port
* @param redPin  	The Red LED Pin
*
* @param greenPort 	The Green LED Port
* @param greenPin  	The Green LED Pin
*
* @param bluePort	The Blue LED Port
* @param bluePin	The Blue LED Pin
*
* @return RGBLEDHandle a pointer to an RGB_LED_Object
*/
#ifdef FREEDOM
RGBLEDHandle RGBLED_Constructor(void *pmemory, const size_t numbytes, GPIO_Type *redPort, uint32_t redPin,
		GPIO_Type *greenPort, uint32_t greenPin,GPIO_Type *bluePort,uint32_t bluePin);
#else
/**
* @brief Constructor for RGB LED object
*
* Given a chunk of memory, the size of an RGB_LED object this
* function initializes a virtual LED and returns a pointer to the object
*
* @param pmemory	The pointer to the memory that this object will use
* @param numbytes	The expected size of the object
*
* @return RGBLEDHandle a pointer to an RGB_LED_Object
*/
RGBLEDHandle RGBLED_Constructor(void *pmemory, const size_t numbytes);
#endif

/**
* @brief Function to turn RGB Elements on or off
*
* Given boolean values for on/off states turn on the RGB elements that the
* object pointer passed to this function represents.
*
* @param RGBLEDHandle	the RGB_LED_Object Pointer
*
* @param red	boolean representing red on (true) or off (false)
* @param green	boolean representing green on (true) or off (false)
* @param blue  	boolean representing blue on (true) or off (false)
*
* @return void
*/
void RGBLED_set(RGBLEDHandle handle, bool red, bool green, bool blue);

/**
* @brief Function to print the status of the RGB object
*
* Given boolean values representing which LEDS you want to print this function
* prints the LED color and whether it is on or not
*
* @param RGBLEDHandle	the RGB_LED_Object Pointer
*
* @param red	boolean representing whether or not to print info about the red LED
* @param green	boolean representing whether or not to print info about the green LED
* @param blue  	boolean representing whether or not to print info about the blue LED
*
* @return void
*/
void RGBLED_printStatus(RGBLEDHandle handle, bool red, bool green, bool blue);


#endif /* SRC_LED_RGB_H_ */
