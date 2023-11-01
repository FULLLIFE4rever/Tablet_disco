/*
 * menu.c
 *
 *  Created on: 8 ?????». 2022 ??.
 *      Author: zub1
 */
#include "menu.h"
#include "USBD_def.h"
#include "usbd_core.h"
extern USBD_HandleTypeDef hUsbDeviceFS;

uint8_t bottle[20] = "Counter: 0";
uint8_t battle = 0x41;
uint16_t backgnd = DISPLAY_BLACK;
uint8_t counter = 0;
uint8_t counter1 = 0;
uint8_t host_com_port_open = 0;
uint32_t* pointer_to_USB = (uint32_t*)0x50000808;

void
Menu_Init(void)
{
  WS2812_Init();
  Display_Init();
  Buttons_Set(0, GPIOB, GPIO_PIN_0, Sleep_Slp, Sleep_Slp);
  Display_FillScreen(backgnd);
}

void
Menu(void)
{

  Buttons_Read();
  Display_Print(bottle, &Cirilic, 10, 40, DISPLAY_WHITE, backgnd);
  //Display_DrawHorisontalLine(1,1,238,0xFFFF);
  sprintf(bottle,"Counter : %4d", counter1);
  counter++;
  if(counter == 10) {counter1++;counter=0;}

  Display_Print(bottle, &Cirilic, 10, 40, DISPLAY_MAGENTA, backgnd);
  //Display_DrawHorisontalLine(1,1,238,0xFFFF);
  //Display_DrawHorisontalLine(3,1,210,0xFFFF);
  if(battle-(*pointer_to_USB) == 0)host_com_port_open = 0;
  battle = *pointer_to_USB;
}
void
inc(void)
{
  battle++;
}
void
dec(void)
{
  battle--;
}
