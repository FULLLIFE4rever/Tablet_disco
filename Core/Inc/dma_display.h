/*
 * dma_display.h
 *
 *  Created on: 22 рту. 2022 у.
 *      Author: zub1
 */

#ifndef INC_DMA_DISPLAY_H_
#define INC_DMA_DISPLAY_H_


#define STM32F4


#include "stdio.h"
#include "spi.h"
#ifdef STM32F4
#include "stm32f4xx_hal_spi.h"
#elif STM32L4
#include "stm32l4xx_hal.h"
#else
#error Please define STM32F4 or STM32L4 depanding on your MK
#endif


#define DISPLAY_DMA_HALF_BUFF 640

#define DISPLAY_HEIGHT 320
#define DISPLAY_WIDTH 240

#define DISPLAY_SPI hspi1

#define DISPLAY_DMA hdma_spi1_tx;


extern DMA_HandleTypeDef DISPLAY_DMA;

typedef enum
{
	DISPLAY_READY,
	DISPLAY_BUSY,
	DISPLAY_ERROR
}DISPLAY_DMA_STATE;

typedef enum
{
	DISPLAY_NO_MSG,
	DISPLAY_NEW_MSG
}DISPLAY_BUFFER_STATE;

void Display_SetPoint(uint8_t X,uint8_t Y);
void Display_ResetPoint(uint8_t X,uint8_t Y);
DISPLAY_DMA_STATE Display_State(void);
DISPLAY_DMA_STATE Display_DMA_Start(uint16_t size);
#endif /* INC_DMA_DISPLAY_H_ */
