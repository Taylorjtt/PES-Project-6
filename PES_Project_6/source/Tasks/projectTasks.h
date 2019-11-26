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
 * @file tasks.h
 * @brief
 *
 *  @author John Taylor
 * 	@date Nov 22, 2019
 *
 */
#ifndef TASKS_PROJECTTASKS_H_
#define TASKS_PROJECTTASKS_H_
#include <stdint.h>
#include "fsl_debug_console.h"
#include "fsl_dac.h"
#include "PES_Project_6.h"

void updateTime(void *p);
void updateDAC(void *p);
void readADC(void *p);
void doDSP(void *p);
#endif /* TASKS_PROJECTTASKS_H_ */
