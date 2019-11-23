/*
 * RingBuffer.h
 *
 *  Created on: Nov 8, 2019
 *      Author: john
 */

#ifndef RINGBUFFER_RINGBUFFER_H_
#define RINGBUFFER_RINGBUFFER_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <string.h>

typedef enum {BUFFER_FULL_ERROR,BUFFER_EMPTY_ERROR, NO_ERROR}BUFFER_ERROR;

typedef struct RING_BUFF_OBJ
{
	uint8_t * buffer;
	uint8_t * head;
	uint8_t * tail;
	uint32_t length;
	uint32_t count;
	bool isInitialized;
}RingBufferObject;

typedef struct RING_BUFF_OBJ *RingBufferHandle;

/**
* @brief Constructor for RingBuffer object
*
* Given a chunk of memory, the size of an RingBuffer object, initialize a RingBuffer
*
* @param pmemory	The pointer to the memory that this object will use
* @param numbytes	The expected size of the object
* @param bufferSize	bufferSize initial size of the buffer
* @return RingBufferHandle a pointer to a RingBuffer
*/
RingBufferHandle RingBuffer_Constructor(void *pmemory, const size_t numbytes, const size_t bufferSize);
/**
* @brief push a byte to the ringbuffer
*
*
* @param handle	pointer to a RingBuffer
* @param data	data to push
* @return BUFFER_ERROR success/fail
*/
BUFFER_ERROR RingBuffer_push(RingBufferHandle handle, uint8_t data);
/**
* @brief pop a byte off the ringbuffer
*
*
* @param handle	pointer to a RingBuffer
* @return BUFFER_ERROR success/fail
*/
BUFFER_ERROR RingBuffer_pop(RingBufferHandle handle);
/**
* @brief read the next value in the queue
*
*
* @param handle	pointer to a RingBuffer
* @return the next char
*/
uint8_t RingBuffer_peek(RingBufferHandle handle);
/**
* @brief get the size of the ringBuffer
*
*
* @param handle	pointer to a RingBuffer
* @return size of the buffer
*/
size_t RingBuffer_getSize(RingBufferHandle handle);
/**
* @brief return if the buffer is Full
*
*
* @param handle	pointer to a RingBuffer
* @return true if full, false if not full
*/
bool RingBuffer_isFull(RingBufferHandle handle);
/**
* @brief return if the buffer is empty
*
*
* @param handle	pointer to a RingBuffer
* @return false if not empty, true if empty
*/
bool RingBuffer_isEmpty(RingBufferHandle handle);
/**
* @brief return if the buffer is valid
*
*
* @param handle	pointer to a RingBuffer
* @return false if not valid, true if valid
*/
bool RingBuffer_isValid(RingBufferHandle handle);
/**
* @brief destroy the buffer
*
*
* @param handle	pointer to a RingBuffer
*/
void RingBuffer_destroy(RingBufferHandle handle);


#endif /* RINGBUFFER_RINGBUFFER_H_ */
