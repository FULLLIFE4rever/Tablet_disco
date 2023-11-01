/*
 * button_it.c
 *
 *  Created on: Jul 5, 2022
 *      Author: zub1
 */
#include "buttons_it.h"
#include "main.h"

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles EXTI line0 interrupt.
 */

button_t Buttons[BUTTONS_NUMBER];

uint16_t
Buttons_Read(void)
{
  // uint8_t temp;
  for (uint8_t i = 0; i < BUTTONS_NUMBER; i++) {
    if (Buttons[i].Press) {
      Buttons[i].Buttons_Press();
      Buttons[i].Press = 0;
    }
    if (Buttons[i].LongPress) {
      Buttons[i].Buttons_LongPress();
      Buttons[i].LongPress = 0;
    }
  }
  return 0;
}

BUTTON_INIT_STATE
Buttons_Set(uint8_t button_num,
            GPIO_TypeDef* GPIOx,
            uint32_t Pin_Num,
            void (*Buttons_Press)(),
            void (*Buttons_LongPress)())
{
  if (button_num >= BUTTONS_NUMBER)
    return BUTTON_OUTOFRANGE;
  Buttons[button_num].GPIOx = GPIOx;
  Buttons[button_num].Pin_num = Pin_Num;
  Buttons[button_num].Buttons_Press = Buttons_Press;
  Buttons[button_num].Buttons_LongPress = Buttons_LongPress;
  return BUTTON_OK;
}

void
HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  uint8_t i, j;
  for (i = 0; i < BUTTONS_NUMBER; i++) {
    if (GPIO_Pin == Buttons[i].Pin_num) {
    	j = HAL_GPIO_ReadPin(Buttons[i].GPIOx, GPIO_Pin);
      if (j) {
        Buttons[i].button_end = HAL_GetTick() - Buttons[i].button_count;
        if (Buttons[i].button_end > 3000) {
          Buttons[i].Press = 0;
          Buttons[i].LongPress = 1;
        } else if (Buttons[i].button_end > 50) {
          Buttons[i].Press = 1;
          Buttons[i].LongPress = 0;
        } else {
        };
      }
    	if(!j){
        Buttons[i].button_count = HAL_GetTick();
      }
    }
  }
}
