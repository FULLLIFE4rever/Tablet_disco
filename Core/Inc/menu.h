/*
 * menu.h
 *
 *  Created on: 8 июл. 2022 г.
 *      Author: zub1
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_

#include "buttons_it.h"
#include "spi_display.h"
#include "battary_life.h"
#include "fonts.h"
#include "sleep.h"
#include <stdio.h>
//#include "ILI9341_STM32_Driver.h"
//#include "ILI9341_GFX.h"
#include "spi.h"
void Menu_Init(void);
void Menu(void);

void inc(void);
void dec(void);
#endif /* INC_MENU_H_ */
