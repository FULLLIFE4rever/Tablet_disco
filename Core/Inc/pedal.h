/*
 * pedal.h
 *
 *  Created on: 28 июн. 2022 г.
 *      Author: zub1
 */

#ifndef INC_PEDAL_H_
#define INC_PEDAL_H_

#include "stm32f4xx_hal.h"

enum pedal_state
{
  PEDAL_OK,
  PEDAL_RELEASED = 0x0A,
  PEDAL_PRESSED = 0x50,
  PEDAL_ERROR = 0xFF

};
uint8_t
Pedal_Init(void);
uint8_t
Pedal_State(void);
#endif /* INC_PEDAL_H_ */
