/*
 * buttons_it.h
 *
 *  Created on: Jul 5, 2022
 *      Author: zub1
 */

#ifndef INC_BUTTONS_IT_H_
#define INC_BUTTONS_IT_H_

#include "stm32f4xx_hal.h"

#define BUTTONS_NUMBER 1
extern TIM_HandleTypeDef htim1;
typedef enum
{
  BUTTON_RELEASED,
  BUTTON_PRESSED
} BUTTON_STATE;

typedef enum
{
  BUTTON_UP = 0x4,
  BUTTON_DOWN,
  BUTTON_MENU,
  BUTTON_UP_MENU,
  BUTTON_SELECT,
  BUTTON_ENTER,

} BUTTONS_t;

typedef enum
{
  BUTTON_OK,
  BUTTON_ERROR,
  BUTTON_OUTOFRANGE

} BUTTON_INIT_STATE;
/*
 Структура для обработки нажатий на кнопку
 */
typedef struct
{
  GPIO_TypeDef* GPIOx;
  uint16_t Pin_num;
  void (*Buttons_Press)();
  void (*Buttons_LongPress)();
  uint32_t button_count;
  uint32_t button_end;
  uint8_t Press : 1;
  uint8_t LongPress : 1;
} button_t;

uint16_t
Buttons_Read(void);
BUTTON_INIT_STATE
Buttons_Set(uint8_t button_num,
            GPIO_TypeDef* GPIOx,
            uint32_t Pin_Num,
            void (*Buttons_Press)(),
            void (*Buttons_LongPress)());

#endif /* INC_BUTTONS_IT_H_ */
