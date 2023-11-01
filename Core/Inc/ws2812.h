#ifndef __WS2812
#define __WS2812

#ifndef WS2812_DIODROWS
#define WS2812_DIODROWS 12
#endif

#ifndef WS2812_DIODCOLS
#define WS2812_DIODCOLS 8
#endif

#define WS2812_SINGLE 24

#define WS2812_DIOD WS2812_DIODCOLS* WS2812_DIODROWS

#define TIM_NUM 4                ///< Timer number
#define TIM_CH TIM_CHANNEL_2     ///< Timer's PWM channel
#define DMA_HANDLE hdma_tim4_ch2 ///< DMA Channel
#define DMA_SIZE_WORD ///< DMA Memory Data Width: {.._BYTE, .._HWORD, .._WORD}

#include "stm32f4xx_hal.h"
#include <string.h>

typedef enum WS2812_STATE
{
  WS2812_READY = 0,     ///< DMA Transfer in progress
  WS2812_BUSY = 1,      ///< DMA Ready to transfer
  WS2812_OK = 2,        ///< Function execution success
  WS2812_PARAM_ERR = 3, ///< Error in input parameters
  WS2812_LEDERR,
  WS2812_ROWERR,
  WS2812_COLERR
} WS2812_STATE;

typedef struct
{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} ws2812color_t;

void
WS2812_Init(void);
void
WS2812_SetColour(uint8_t red, uint8_t green, uint8_t blue, uint16_t pos);
WS2812_STATE
WS2812_SetColour_t(ws2812color_t byte_buf, uint16_t pos);
WS2812_STATE
WS2812_Status(void);
void
WS2812_Clear(void);
void
WS2812_SetLed(uint8_t colR,
              uint8_t colG,
              uint8_t colB,
              uint16_t ledX,
              uint16_t ledY);
void
WS2812_SetCol(uint8_t colR, uint8_t colG, uint8_t colB, uint16_t ledX);
void
WS2812_SetRow(uint8_t colR, uint8_t colG, uint8_t colB, uint16_t ledY);
WS2812_STATE
WS2812_SetRow_t(ws2812color_t color, uint16_t ledX);
WS2812_STATE
WS2812_SetCol_t(ws2812color_t color, uint16_t ledY);
void
WS2812_Print(uint8_t colR, uint8_t colG, uint8_t colB, uint16_t* font);
WS2812_STATE
WS2812_Send(void);

#endif
