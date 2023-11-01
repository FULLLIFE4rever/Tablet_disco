/*
 * font_format.h
 *
 *  Created on: 19 èþë. 2022 ã.
 *      Author: zub1
 */

#ifndef INC_FONT_FORMAT_H_
#define INC_FONT_FORMAT_H_

#include <stdint.h>

typedef struct
{
	const uint8_t height;
	const uint8_t width;
	const uint16_t* font;
}font16_t;

typedef struct
{
	const uint8_t height;
	const uint8_t width;
	const uint8_t* font;
}font8_t;

#endif /* INC_FONT_FORMAT_H_ */
