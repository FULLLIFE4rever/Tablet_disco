/*
 * serial.h
 *
 *  Created on: 10 июн. 2022 г.
 *      Author: zub1
 */

#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_

/* USER CODE BEGIN Includes */
#ifndef SIZE_OF_BUF
#define SIZE_OF_BUF 256
#endif
#include "main.h"
#include "pedal.h"
#include "usbd_cdc_if.h"
#include "ws2812.h"

#define START_BYTE 0xB7
#define STOP_BYTE 0xC7

#define HASH(x, y) x ^ y

extern uint8_t UserRxBufferFS[];
extern ws2812color_t color_buf[WS2812_DIOD];
extern uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

typedef enum
{
  STATE_OK,
  LENGTH_MISMATCH,
  CHECKSUM_MISMATCH,
  START_BYTE_MISMATCH,
  STOP_BYTE_MISMATCH,
  INVALID_CMD,
  INVALID_OPERANDS,
  INVALID_LED_ADDRESS,
  INVALID_LED_COLOR
} errorCode;

typedef enum
{
  CMD_CLEAR = 0x0A,
  CMD_SET_LED = 0x0B,
  CMD_SET_ROW = 0x0C,
  CMD_SET_COL = 0x0D,
  CMD_SET_FRAME = 0x0E,
  CMD_READ_LED = 0x10,
  CMD_READ_FRAME = 0x11,
  CMD_READ_PEDAL = 0x12,
  CMD_PEDAL_PRESSED = 0x1A,
  CMD_PEDAL_RELEASED = 0x1B,
  CMD_PING = 0xAA,
} serialCommands;

/* USER CODE END Includes */

extern uint8_t
CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);
extern WS2812_STATE
WS2812_SetColour_t(ws2812color_t byte_buf, uint16_t pos);
extern ws2812color_t
WS2812_2bitTo8bit(uint8_t byte_buf);

void
Serial_Write(uint8_t cmd, uint8_t err, uint8_t num);
uint8_t
Serial_Read(uint8_t* buf, uint8_t len);
errorCode
Serial_CheckHash(uint8_t* buf, uint8_t len);
#endif /* INC_SERIAL_H_ */
