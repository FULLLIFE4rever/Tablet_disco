/*
 * dma_display.c
 *
 *  Created on: 22 авг. 2022 г.
 *      Author: zub1
 */

#include "dma_display.h"

uint8_t display_dma_buff[DISPLAY_DMA_HALF_BUFF * 2] = {0};
uint8_t display_trans_counter;
uint16_t display_trans_num =
    DISPLAY_HEIGHT * DISPLAY_WIDTH / DISPLAY_DMA_HALF_BUFF;
//Буффер кадра из драйвера дисплея
uint8_t display_state;
uint8_t Frame_buffer[DISPLAY_HEIGHT * DISPLAY_WIDTH / 8];
uint8_t display_switch = DISPLAY_NO_MSG;

DISPLAY_DMA_STATE Display_State(void) { return display_state; }

void Display_SetPoint(uint8_t X, uint8_t Y) {
  uint8_t Point = (X + Y * DISPLAY_HEIGHT) / 8;
  Frame_buffer[Point] |= (1 << X % 8);
  display_switch = DISPLAY_NEW_MSG;
}

void Display_ResetPoint(uint8_t X, uint8_t Y) {
  uint8_t Point = (X + Y * DISPLAY_HEIGHT) / 8;
  Frame_buffer[Point] &= ~(1 << X % 8);
  display_switch = DISPLAY_NEW_MSG;
}

DISPLAY_DMA_STATE Display_DMA_Start(uint16_t size) {
  display_state = DISPLAY_BUSY;
  if (display_switch == 1) {
    for (uint8_t i = 0; i < DISPLAY_DMA_HALF_BUFF; i++) {
      display_dma_buff[i] =
          (Frame_buffer[i / 8] & (1 << (i % 8))) ? 0xFFFF : 0x0000;
      display_dma_buff[i + DISPLAY_DMA_HALF_BUFF] =
          (Frame_buffer[(i + DISPLAY_DMA_HALF_BUFF) / 8] & (1 << (i % 8)))
              ? 0xFFFF
              : 0x0000;
    }
    display_state = HAL_SPI_Transmit_DMA(&DISPLAY_SPI, display_dma_buff,
                                         DISPLAY_DMA_HALF_BUFF * 2);
    if (display_state == HAL_SPI_STATE_ERROR) {display_state=DISPLAY_ERROR;goto error;}
    if(display_state !=HAL_SPI_STATE_READY){display_state=DISPLAY_BUSY;goto error;}
    display_trans_counter = 2;
    display_switch = DISPLAY_NO_MSG;
  }
error:
  return display_state;
}

void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi) {
  if (display_trans_counter == 0) {
    HAL_SPI_DMAStop(hspi);display_state = DISPLAY_READY;return;
  }
  for (uint8_t i = 0; i < DISPLAY_DMA_HALF_BUFF; i++)
    display_dma_buff[i] =
        (Frame_buffer[i / 8 + display_trans_counter * DISPLAY_DMA_HALF_BUFF] &
         (1 << (i % 8)))
            ? 0xFFFF
            : 0x0000;
  display_trans_counter++;
  display_trans_counter %= display_trans_num;
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
  if (display_trans_counter == 0) {
    HAL_SPI_DMAStop(hspi);
    display_state = DISPLAY_READY;
    return;
  }
  for (uint8_t i = 0; i < DISPLAY_DMA_HALF_BUFF; i++)
    display_dma_buff[i] =
        (Frame_buffer[i / 8 + display_trans_counter * DISPLAY_DMA_HALF_BUFF] &
         (1 << (i % 8)))
            ? 0xFFFF
            : 0x0000;
  display_trans_counter++;
  display_trans_counter %= display_trans_num;
}
