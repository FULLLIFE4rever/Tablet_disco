/*
 * swo.h
 *
 *  Created on: 9 июн. 2022 г.
 *      Author: zub1
 */

#ifndef INC_SWO_H_
#define INC_SWO_H_
#define DEMCR *((volatile uint32_t*)0xE000EDFCu)

/* ITM register addresses */
#define ITM_STIMULUS_PORT0 *((volatile uint32_t*)0xE0000000u)
#define ITM_TRACE_EN *((volatile uint32_t*)0xE0000E00u)

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <time.h>

void
ITM_SendChar(uint8_t ch);

#endif /* INC_SWO_H_ */
