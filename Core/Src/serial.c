/*
 * serial.c
 *
 *  Created on: 10 июн. 2022 г.
 *      Author: zub1
 */
#define SIZE_CLEAR 4
#define SIZE_SET_LED 6
#define SIZE_SET_ROW 6
#define SIZE_SET_COL 6
#define SIZE_SET_FRAME 4 + 96
#define SIZE_SET_PEDAL 5
#define SIZE_READ_LED 5
#define SIZE_READ_FRAME 4
#define SIZE_READ_PEDAL 4
#define SIZE_PEDAL_PRESSED 5
#define SIZE_PEDAL_RELEASED 5
#define SIZE_PING 5

#include "serial.h"

/**
 * @brief  Read package from USB
 * @param  buf Recive buffer
 * @param  len Length of recived buffer
 * @retval HAL status
 */

uint8_t
Serial_Read(uint8_t* buf, uint8_t len)
{
  uint8_t error = STATE_OK;
  ws2812color_t color_fs;
  uint8_t num = 0;
  if (len != 0) {

    if (buf[len - 2] != Serial_CheckHash(buf, len - 2))
      error = CHECKSUM_MISMATCH;
    if (buf[len - 1] != STOP_BYTE)
      error = STOP_BYTE_MISMATCH;
    if (buf[0] != START_BYTE)
      error = START_BYTE_MISMATCH;
    if (error == STATE_OK) {

      switch (buf[1]) {
        case CMD_CLEAR:
          if (len == SIZE_CLEAR) {
            WS2812_Clear();
          } else
            error = LENGTH_MISMATCH;
          break;
        case CMD_SET_LED:
          if (len == SIZE_SET_LED) {
            error = WS2812_SetColour_t(WS2812_2bitTo8bit(UserRxBufferFS[3]),
                                       UserRxBufferFS[2]);
          } else
            error = LENGTH_MISMATCH;
          break;
        case CMD_SET_ROW:
          if (len == SIZE_SET_ROW) {
            color_fs = WS2812_2bitTo8bit(UserRxBufferFS[3]);
            error = WS2812_SetRow_t(color_fs, UserRxBufferFS[2]);
          } else
            error = LENGTH_MISMATCH;
          break;
        case CMD_SET_COL:
          if (len == SIZE_SET_COL) {
            color_fs = WS2812_2bitTo8bit(UserRxBufferFS[3]);
            error = WS2812_SetCol_t(color_fs, UserRxBufferFS[2]);
          } else
            error = LENGTH_MISMATCH;
          break;
        case CMD_SET_FRAME:
          if (len == SIZE_SET_FRAME) {
            for (uint8_t i = 0; i < 96; i++) {
              color_fs = WS2812_2bitTo8bit(UserRxBufferFS[3 + i]);
              error = WS2812_SetColour_t(color_fs, i);
            }
          } else
            error = LENGTH_MISMATCH;
          break;
        case CMD_READ_LED:
          if (len == SIZE_READ_LED) {
            if (UserRxBufferFS[2] < WS2812_DIOD)
              num = UserRxBufferFS[2];
            else {
              error = INVALID_LED_ADDRESS;
            }
          } else {
            error = LENGTH_MISMATCH;
          }
          break;
        case CMD_READ_FRAME:
          break;
        case CMD_READ_PEDAL:
          break;
        case CMD_PEDAL_PRESSED:
          break;
        case CMD_PEDAL_RELEASED:
          break;
        case CMD_PING:
          break;
        default:
          error = INVALID_CMD;
          break;
      }
    }
    if (buf[1] >= CMD_CLEAR || buf[1] < CMD_READ_LED ||
        error != LENGTH_MISMATCH) {
      WS2812_Send();
    }
    Serial_Write(buf[1], error, num);
  }

  return error;
}

/**
 * @brief  Формирование и отправка сообщения по U(S)ART
 * @param  huart Pointer to a UART_HandleTypeDef structure that contains
 *               the configuration information for the specified UART.
 * @param  cmd принятая команда
 * @param  err Наличие ошибки при приёме сообщения из списка errorCode
 * @retval none
 */

void
Serial_Write(uint8_t cmd, uint8_t err, uint8_t num)
{
  uint8_t len;
  UserTxBufferFS[0] = START_BYTE;
  switch (cmd) {
    case CMD_CLEAR:
    case CMD_SET_LED:
    case CMD_SET_ROW:
    case CMD_SET_COL:
    case CMD_SET_FRAME:
      len = 5;
      UserTxBufferFS[1] = cmd;
      UserTxBufferFS[2] = err;
      UserTxBufferFS[3] = Serial_CheckHash(UserTxBufferFS, 3);
      UserTxBufferFS[4] = STOP_BYTE;
      break;
    case CMD_READ_LED:
      len = 6;
      UserTxBufferFS[1] = cmd;
      UserTxBufferFS[2] = num;
      UserTxBufferFS[3] = ((color_buf[num].red * 3 / 126) << 5) |
                          ((color_buf[num].green * 3 / 126) << 3) |
                          ((color_buf[num].blue * 3 / 126) << 1);
      UserTxBufferFS[4] = Serial_CheckHash(UserTxBufferFS, 4);
      UserTxBufferFS[5] = STOP_BYTE;
      break;
    case CMD_READ_FRAME:
      len = 100;
      uint8_t i = 0;
      UserTxBufferFS[1] = cmd;
      for (i = 0; i < WS2812_DIOD; i++)
        UserTxBufferFS[2 + i] = ((color_buf[i].red * 3 / 126) << 5) |
                                ((color_buf[i].green * 3 / 126) << 3) |
                                ((color_buf[i].blue * 3 / 126) << 1);
      UserTxBufferFS[2 + i] = Serial_CheckHash(UserTxBufferFS, 2 + i);
      UserTxBufferFS[3 + i] = STOP_BYTE;
      break;
    case CMD_READ_PEDAL:
      len = 5;
      UserTxBufferFS[1] = cmd;
      UserTxBufferFS[2] = Pedal_State();
      UserTxBufferFS[3] = Serial_CheckHash(UserTxBufferFS, 3);
      UserTxBufferFS[4] = STOP_BYTE;
      break;
    case CMD_PEDAL_PRESSED:
      break;
    case CMD_PEDAL_RELEASED:
      break;
    case CMD_PING:
      break;
    default:
      err = INVALID_CMD;
      break;
  }
  CDC_Transmit_FS(UserTxBufferFS, len);
}

/**
 * @brief  Hash summ
 * @param  buf buffer to calculate
 * @param  len Length buffer to calculate
 * @retval HAL status
 */

uint8_t
Serial_CheckHash(uint8_t* buf, uint8_t len)
{
  uint8_t hash = 0, i;

  for (i = 1; i < len; i++) {
    hash ^= buf[i];
  }

  return hash;
}
