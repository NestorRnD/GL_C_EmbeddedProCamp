/*
 * Inline function for converting RGB888 to RGB565
 *   (c) Nestor Tyshko, email:tyshko.n@gmail.com
 */


#ifndef MY_COLOR_CONV_H
#define MY_COLOR_CONV_H

#include <stdint.h>

static inline uint16_t rgb888_to_rgb565(uint32_t rgb888)
{
    return
	((rgb888 & 0xf8)>>3)|	 // R
	((rgb888 & 0xfc00)>>5)|	 // G
	((rgb888 & 0xf80000)>>8);// B
}

#endif
