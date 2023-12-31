/*
 * battary_life.h
 *
 *  Created on: 19 ���. 2022 �.
 *      Author: zub1
 */
#include "battary_life.h"

const uint8_t Bat_Fnt[] = {
  0xFF, 0x81, 0xBD, 0x81, 0xBD, 0x81,
  0xBD, 0x81, 0xBD, 0x81, 0xFF, 0x3C, // Code for char num #0
  0xFF, 0x81, 0xBD, 0x81, 0xBD, 0x81,
  0xBD, 0x81, 0x81, 0x81, 0xFF, 0x3C, // Code for char num #1
  0xFF, 0x81, 0xBD, 0x81, 0xBD, 0x81,
  0x81, 0x81, 0x81, 0x81, 0xFF, 0x3C, // Code for char num #2
  0xFF, 0x81, 0xBD, 0x81, 0x81, 0x81,
  0x81, 0x81, 0x81, 0x81, 0xFF, 0x3C, // Code for char num #3
  0xFF, 0x81, 0x81, 0x81, 0x81, 0x81,
  0x81, 0x81, 0x81, 0x81, 0xFF, 0x3C // Code for char num #4
};

const uint8_t title12x8[] = {
  0xFF, 0x0F, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01,
  0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0xFF, 0x0F, // Code for char num #0
  0xFF, 0x0E, 0x80, 0x02, 0xB0, 0x03, 0xB0, 0x03,
  0xB0, 0x03, 0xB0, 0x03, 0x80, 0x02, 0xFF, 0x0E, // Code for char num #1
  0xFF, 0x0E, 0x80, 0x02, 0xB6, 0x03, 0xB6, 0x03,
  0xB6, 0x03, 0xB6, 0x03, 0x80, 0x02, 0xFF, 0x0E, // Code for char num #2
  0xFF, 0x0E, 0x80, 0x02, 0xB6, 0x0B, 0xB6, 0x0B,
  0xB6, 0x0B, 0xB6, 0x0B, 0x80, 0x02, 0xFF, 0x0E, // Code for char num #3
  0xFF, 0x0E, 0x80, 0x02, 0x86, 0x0B, 0x86, 0x0B,
  0x86, 0x0B, 0x86, 0x0B, 0x80, 0x02, 0xFF, 0x0E, // Code for char num #4
  0xFF, 0x0E, 0x80, 0x02, 0x80, 0x03, 0x80, 0x03,
  0x80, 0x03, 0x80, 0x03, 0x80, 0x02, 0xFF, 0x0E // Code for char num #5
};

font8_t Battary = { 8, 12, Bat_Fnt };
font8_t Battary1 = { 12, 8,  title12x8 };
