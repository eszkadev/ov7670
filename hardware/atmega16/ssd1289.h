/*
 * SSD1289
 * Author: Szymon Kłos
*/

#ifndef _SSD1289_
#define _SSD1289_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <string.h>

#include "ssd1289_config.h"
#ifndef PARALLEL_MODE
	#include "shift.h"
#endif

enum
{
	COMMAND,
	DATA
};

uint16_t RGB(uint8_t r, uint8_t g, uint8_t b);

void SSD1289_Write(short type, uint16_t data);
void SSD1289_WriteCommand(uint16_t address, uint16_t data);

void SSD1289_DisplayON(void);
void SSD1289_SleepMode(void);
void SSD1289_ReleaseFromSleep(void);

void SSD1289_Init(void);

void SetCursor(uint16_t x, uint16_t y);
void SetArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
inline void DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
					uint16_t color);
void FillScreen(uint16_t color);

#endif
