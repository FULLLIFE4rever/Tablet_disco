/*
 * spi_dicplay.c
 *
 *  Created on: Jul 11, 2022
 *      Author: zub1
 */

#include "spi_display.h"

uint8_t data[16];

void Display_OFF(void)
{
	Display_Command(DISPLAY_DISPLAY_OFF);
}

void Display_ON(void)
{
	Display_Command(DISPLAY_DISPLAY_ON);
}

void
Display_Init(void)
{
	RESET_ON();
	  CS_ON();
	  RESET_OFF();
	  HAL_Delay(200);

	  CS_OFF();
	  RESET_ON();
	  Display_Command(DISPLAY_RESET);

	  data[0] = 0x39;
	  data[1] = 0x2C;
	  data[2] = 0x00;
	  data[3] = 0x34;
	  data[4] = 0x02;

	  Display_Command(DISPLAY_POWERA);
	  Display_Data(data, 5);

	  data[0] = 0x00;
	  data[1] = 0xC1;
	  data[2] = 0x30;
	  Display_Command(DISPLAY_POWERB);
	  Display_Data(data, 3);
	  data[0] = 0x85;
	  data[1] = 0x00;
	  data[2] = 0x78;
	  Display_Command(DISPLAY_DTCA);
	  data[0] = 0x00;
	  data[1] = 0x00;
	  Display_Command(DISPLAY_DTCB);
	  Display_Data(data, 2);

	  data[0] = 0x64;
	  data[1] = 0x03;
	  data[2] = 0x12;
	  data[3] = 0x81;
	  Display_Command(DISPLAY_POWER_SEQ);
	  Display_Data(data, 4);
	  data[0] = 0x20;
	  Display_Command(DISPLAY_PRC);
	  Display_Data(data, 1);
	  data[0] = 0x10;
	  Display_Command(DISPLAY_POWER1);
	  Display_Data(data, 1);
	  Display_Command(DISPLAY_POWER2);
	  Display_Data(data, 1);
	  data[0] = 0x3E;
	  data[1] = 0x28;
	  Display_Command(DISPLAY_VCOM1);
	  Display_Data(data, 2);
	  data[0] = 0x86;
	  Display_Command(DISPLAY_VCOM2);
	  Display_Data(data, 1);
	  data[0] = DISPLAY_MAC_PARAMS;
	  Display_Command(DISPLAY_MAC);
	  Display_Data(data, 1);
	  data[0] = DISLAY_16BIT;
	  Display_Command(DISPLAY_PIXEL_FORMAT);
	  Display_Data(data, 1);
	  data[0] = 0x00;
	  data[1] = 0x18;
	  Display_Command(DISPLAY_FRC);
	  Display_Data(data, 2);
	  data[0] = 0x08;
	  data[1] = 0x82;
	  data[2] = 0x27;
	  Display_Command(DISPLAY_DFC);
	  Display_Data(data, 3);

	  data[0] = 0x01;
	  Display_Command(DISPLAY_GAMMA);
	  Display_Data(data, 1);
	  data[0] = 0x00;
	  Display_Command(0xF2);
	  Display_Data(data, 1);
	  data[0] = 0x0F;
	  data[1] = 0x31;
	  data[2] = 0x2B;
	  data[3] = 0x0C;
	  data[4] = 0x0E;
	  data[5] = 0x08;
	  data[6] = 0x4E;
	  data[7] = 0xF1;
	  data[8] = 0x37;
	  data[9] = 0x07;
	  data[10] = 0x10;
	  data[11] = 0x03;
	  data[12] = 0x0E;
	  data[13] = 0x09;
	  data[14] = 0x00;
	  Display_Command(DISPLAY_PGAMMA);
	  Display_Data(data, 15);
	  data[0] = 0x00;
	  data[1] = 0x0E;
	  data[2] = 0x14;
	  data[3] = 0x03;
	  data[4] = 0x11;
	  data[5] = 0x07;
	  data[6] = 0x31;
	  data[7] = 0xC1;
	  data[8] = 0x48;
	  data[9] = 0x08;
	  data[10] = 0x0F;
	  data[11] = 0x0C;
	  data[12] = 0x31;
	  data[13] = 0x36;
	  data[14] = 0x0F;
	  Display_Command(DISPLAY_NGAMMA);
	  Display_Data(data, 15);
	  Display_Command(DISPLAY_SLEEP_OUT);
	  HAL_Delay(120);
	  Display_Command(DISPLAY_DISPLAY_ON);
	  Display_Command(DISPLAY_IDLE_MODE_OFF);
}

void
Display_Command(uint8_t cmd)
{
  CS_ON();
  DC_COMMAND();
  HAL_SPI_Transmit(&hspi1, &cmd, 1, 1);
  CS_OFF();
}

void
Display_Data(uint8_t* data, uint8_t len)
{
  CS_ON();
  DC_DATA();
  HAL_SPI_Transmit(&hspi1, data, len, 1);
  CS_OFF();
}

void
Display_FillScreen(uint16_t color)
{
  Display_SetPos(0x0, 0x0, 0x13F, 0xEF);

  data[0] = (uint8_t)(color >> 8);
  data[1] = (uint8_t)(color);
  volatile uint32_t i;
  for (i = 0; i < 0x12BFF; i++) {

    Display_Data(data, 2);
  }
}

DISPLAY_STATUS
Display_SetPos(uint16_t X, uint16_t Y, uint16_t Xo, uint16_t Yo)
{
  if (X > 0x13F || Xo > 0x13F || Y > 0xEF || Yo > 0xEF)
    return DISPLAY_ERROR;
  data[0] = (uint8_t)(X >> 8);
  data[1] = (uint8_t)X;
  data[2] = (uint8_t)(Xo >> 8);
  data[3] = (uint8_t)Xo;
  Display_Command(DISPLAY_COLUMN_ADDR);

  Display_Data(data, 4);

  data[0] = (uint8_t)(Y >> 8);
  data[1] = (uint8_t)Y;
  data[2] = (uint8_t)(Yo >> 8);
  data[3] = (uint8_t)Yo;
  Display_Command(DISPLAY_PAGE_ADDR);
  Display_Data(data, 4);
  Display_Command(DISPLAY_GRAM);
  return DISPLAY_OK;
}

void
Display_Battery(uint8_t state,
                font8_t* Font,
				uint16_t X,
				uint16_t Y,
                uint16_t color,
                uint16_t bgcolor)
{
  if(Display_SetPos(X, Y, X + Font->width - 1, Y + Font->height - 1)!=DISPLAY_OK)return;
  uint16_t status;
  for (uint8_t i = 0; i < Font->height; i++)
    for (uint8_t j = 0; j < Font->width; j++) {
      // status = state * Font->width + j * i/8 + i/8;
      status = ((state * Font->width * (((Font->height - 1) / 8) + 1)) +
                (Font->height - 1) / 8 * j + j) +
               i / 8;
      // if ((Font->font[status] >> (Font->height-i-1)%8) & 0x1)
      if ((Font->font[status] << i % 8) & 0x80) {
    	  Display_SetPoint(color);
      } else {
    	  Display_SetPoint(bgcolor);
      }

      Display_Data(data, 2);
    }
}

void
Display_Putc(uint8_t character,
             font8_t* Font,
             uint16_t posX,
             uint16_t posY,
             uint16_t color,
             uint16_t bgcolor)
{
	if(character>191)
		character-=96;
	else
  character -= 32;
  if(Display_SetPos(posX, posY, posX + Font->width - 1, posY + Font->height - 1)!=DISPLAY_OK)return;
  uint16_t status;
  for (uint8_t i = 0; i < Font->height; i++)
    for (uint8_t j = 0; j < Font->width; j++) {
      // status = state * Font->width + j * i/8 + i/8;
      status = ((character * Font->width * (((Font->height - 1) / 8) + 1)) +
                (Font->height - 1) / 8 * j + j) +
               i / 8;
      // if ((Font->font[status] >> (Font->height-i-1)%8) & 0x1)
      if ((Font->font[status] << i % 8) & 0x80) {
    	  Display_SetPoint(color);
      } else {
    	  Display_SetPoint(bgcolor);
      }

    }
}

void Display_Print(uint8_t* String,
		font8_t* Font,
        uint16_t posX,
        uint16_t posY,
        uint16_t color,
        uint16_t bgcolor)
{

	uint8_t space=0,i = 0;
	while(String[i]!=0)
	{
		Display_Putc(String[i],Font,posX,posY+Font->height*i+space,color,bgcolor);
		space++;
		i++;
	}

}
void Display_SetPoint(uint16_t color)
{
    data[0] = (uint8_t)(color >> 8);
    data[1] = (uint8_t)(color >> 0);
    Display_Data(data, 2);
}

void Display_DrawHorisontalLine(uint16_t posX,uint16_t posY,uint16_t Length,uint16_t color)
{
	if(Display_SetPos(posX, posY, posX+Length-1, posY)!=DISPLAY_OK)return;
	for(uint8_t i = 0; i<Length;i++)
		Display_SetPoint(color);
}
void Display_DrawVerticalLine(uint16_t posX,uint16_t posY,uint16_t Length,uint16_t color)
{
	if(Display_SetPos(posX, posY, posX, posY+Length-1) !=DISPLAY_OK)return;
	for(uint8_t i = 0; i<Length;i++)
		Display_SetPoint(color);
}

void Display_DrawRectengle(uint16_t posX,uint16_t posY,uint16_t Xoff,uint16_t Yoff,uint16_t color)
{
	if(Display_SetPos(posX, posY, posX+Xoff-1, posY+Yoff-1) !=DISPLAY_OK)return;
	for(uint8_t i = 0; i<Xoff*Yoff;i++)
		Display_SetPoint(color);
}
