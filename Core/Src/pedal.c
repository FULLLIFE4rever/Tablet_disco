/*
 * pedal.c
 *
 *  Created on: 28 июн. 2022 г.
 *      Author: zub1
 */

#include "pedal.h"

uint8_t
Pedal_Init(void)
{
  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) !=
      HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13))
    return Pedal_State();
  return PEDAL_ERROR;
}

uint8_t
Pedal_State(void)
{
  if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) &&
      HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13))
    return PEDAL_RELEASED;
  else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) &&
           !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13))
    return PEDAL_PRESSED;
  return PEDAL_ERROR;
}
