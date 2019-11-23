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
 * @file logger.c
 * @brief Cross platform Logger
 *
 *  @author John Taylor
 * 	@date Aug 11, 2019
 *
 */

#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_
#define FREEDOM
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "util.h"
#ifdef FREEDOM
#include "fsl_debug_console.h"
#endif
typedef enum {DISABLED,ENABLED}LOGGER_STATUS;
typedef enum {TEST_LEVEL,DEBUG_LEVEL,STATUS_LEVEL}LOG_LEVEL;

typedef struct LOGGER_OBJ
{
	LOGGER_STATUS status;
}LOGGERObject;

typedef struct LOGGER_OBJ *LoggerHandle;

/**
* @brief Constructor for Logger object
*
* Given a chunk of memory, the size of an Logger object, initialize a logger
*
* @param pmemory	The pointer to the memory that this object will use
* @param numbytes	The expected size of the object
* @return LoggerHandle a pointer to an LoggerObject
*/
LoggerHandle Logger_Constructor(void *pmemory, const size_t numbytes);

/**
* @brief Function to enable the logger
*
* @param handle		logger object handle
*/
void Logger_enable(LoggerHandle handle);
/**
* @brief Function to disable the logger
*
* @param handle		logger object handle
*/
void Logger_disable(LoggerHandle handle);
/**
* @brief Function to get whether or not the logger is enabled
*
* @param handle		logger object handle
* @return LOGGER_STATUS indicating whether or not the logger is enabled
*/
LOGGER_STATUS Logger_status(LoggerHandle handle);
/**
* @brief Log a chunk of memory
*
* @param handle		logger object handle
* @param loc		memory location
* @param length		length in bytes of memory chunk
*/
void Logger_logData(LoggerHandle handle, uint8_t* loc, size_t length,const char* function, LOG_LEVEL level);
/**
* @brief Log a string
*
* @param handle		logger object handle
* @param string		string to log
*/
void Logger_logString(LoggerHandle handle, const char * string, const char* function,LOG_LEVEL level);
void Logger_logTime(LoggerHandle handle);
/**
* @brief Log an integer
*
* @param handle		logger object handle
* @param string		int to log
*/
void Logger_logInt(LoggerHandle handle, uint8_t num, const char* function,LOG_LEVEL level);

void Logger_logTemps(LoggerHandle handle, float currentTemp,float averageTemp,const char* function, LOG_LEVEL level);
const char* getLevelString(LOG_LEVEL);
#endif /* LOGGER_LOGGER_H_ */
