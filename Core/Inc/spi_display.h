/*
 * spi_display.h
 *
 *  Created on: Jul 11, 2022
 *      Author: zub1
 */

#ifndef INC_SPI_DISPLAY_H_
#define INC_SPI_DISPLAY_H_


#include "stm32f4xx_hal.h"
#include "font_format.h"

#define DISPLAY_RESET 0x01
#define DISPLAY_SLEEP_OUT 0x11
#define DISPLAY_PARTIAL_MODE 0x12
#define DISPLAY_NORMAL_DISPLAY_MODE 0x13
#define DISPLAY_INVERSION_OFF 0x20
#define DISPLAY_INVERSION_ON 0x21
#define DISPLAY_GAMMA 0x26
#define DISPLAY_DISPLAY_OFF 0x28
#define DISPLAY_DISPLAY_ON 0x29
#define DISPLAY_COLUMN_ADDR 0x2A
#define DISPLAY_PAGE_ADDR 0x2B
#define DISPLAY_GRAM 0x2C
#define DISPLAY_COLOUR_SET 0x2D
#define DISPLAY_PARTIAL_AREA 0x30
#define DISPLAY_VS_DEFINE 0x33
#define DISPLAY_MAC 0x36
#define DISPLAY_VS_START_ADDR 0x37
#define DISPLAY_IDLE_MODE_OFF 0x38
#define DISPLAY_IDLE_MODE_ON 0x39
#define DISPLAY_PIXEL_FORMAT 0x3A
#define DISLAY_16BIT 0x55
#define DISLAY_18BIT 0x66
#define DISPLAY_WRITE_MEM_CONTINUE 0x3C
#define DISPLAY_WDB 0x51
#define DISPLAY_WCD 0x53
#define DISPLAY_RGB_INTERFACE 0xB0
#define DISPLAY_FRC 0xB1
#define DISPLAY_INVERSION_CTRL 0xB4
#define DISPLAY_BPC 0xB5
#define DISPLAY_DFC 0xB6
#define DISPLAY_POWER1 0xC0
#define DISPLAY_POWER2 0xC1
#define DISPLAY_VCOM1 0xC5
#define DISPLAY_VCOM2 0xC7
#define DISPLAY_POWERA 0xCB
#define DISPLAY_POWERB 0xCF
#define DISPLAY_PGAMMA 0xE0
#define DISPLAY_NGAMMA 0xE1
#define DISPLAY_DTCA 0xE8
#define DISPLAY_DTCB 0xEA
#define DISPLAY_POWER_SEQ 0xED
#define DISPLAY_3GAMMA_EN 0xF2
#define DISPLAY_INTERFACE 0xF6
#define DISPLAY_PRC 0xF7

#define RESET_ON() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)
#define RESET_OFF() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define CS_ON() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET)
#define CS_OFF() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET)
#define DC_COMMAND() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET)
#define DC_DATA() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET)

#define DISPLAY_BLACK 0x0000
#define DISPLAY_BLUE 0x0010
#define DISPLAY_RED 0x8000
#define DISPLAY_GREEN 0x0400
#define DISPLAY_CYAN 0x0410
#define DISPLAY_MAGENTA 0x8010
#define DISPLAY_YELLOW 0x8400
#define DISPLAY_WHITE 0x8410

#define DISPLAY_DAC_MY (1 << 7)
#define DISPLAY_DAC_MX (1 << 6)
#define DISPLAY_DAC_MV (1 << 5)
#define DISPLAY_DAC_ML (1 << 4)
#define DISPLAY_DAC_BGR (1 << 3)
#define DISPLAY_DAC_MH (1 << 2)

#define DISPLAY_MAC_PARAMS  DISPLAY_DAC_MX | DISPLAY_DAC_MV

extern SPI_HandleTypeDef hspi1;

typedef enum
{
	DISPLAY_OK,
	DISPLAY_ERROR
}DISPLAY_STATUS;

void Display_OFF(void);
void Display_ON(void);

void
Display_Init(void);
void
Display_Command(uint8_t cmd);
void
Display_Data(uint8_t* data, uint8_t len);
void
Display_FillScreen(uint16_t color);
DISPLAY_STATUS
Display_SetPos(uint16_t X, uint16_t Y, uint16_t Xo, uint16_t Yo);
void
Display_SendCmd(void);
void Display_SetPoint(uint16_t color);
void
Display_Putc(uint8_t character,
             font8_t* Font,
             uint16_t posX,
             uint16_t posY,
             uint16_t color,
             uint16_t bgcolor);
void
Display_Battery(uint8_t state,
                font8_t* Font,
				uint16_t X,
				uint16_t Y,

                uint16_t color,
                uint16_t bgcolor);
void Display_Print(uint8_t* String,

		font8_t* Font,
        uint16_t posX,
        uint16_t posY,
        uint16_t color,
        uint16_t bgcolor);
void Display_DrawVerticalLine(uint16_t posX,uint16_t posY,uint16_t Length,uint16_t color);
void Display_DrawHorisontalLine(uint16_t posX,uint16_t posY,uint16_t Length,uint16_t color);
void Display_DrawRectengle(uint16_t posX,uint16_t posY,uint16_t Xoff,uint16_t Yoff,uint16_t color);
#endif /* INC_SPI_DISPLAY_H_ */
