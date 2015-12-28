#ifndef _LCD_
#define _LCD_

/*
 * Author: Szymon Kłos
*/

#include "config.h"

#ifdef _PLATFORM_ATMEGA16
	#include "atmega16/ssd1289.h"

	inline static void lcd_init(void) __attribute__((always_inline));
	inline static void draw_pixel(uint16_t x, uint16_t y, uint16_t color) __attribute__((always_inline));

	inline static void lcd_init(void)
	{
		SSD1289_Init();
		FillScreen(RGB(0, 0, 0));
	}
	
	inline static void draw_pixel(uint16_t x, uint16_t y, uint16_t color)
	{
		DrawPixel(x, y, color);
	}
#endif

#endif
