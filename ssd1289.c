/*
 * SSD1289
 * Author: Szymon Kłos
*/

#include "ssd1289.h"

inline uint16_t RGB(uint8_t r, uint8_t g, uint8_t b)
{
	// return RGB-565

	r >>= 3;
	g >>= 2;
	b >>= 3;

	return (r << 11) | (g << 5) | b;
}

inline void SSD1289_Write(short type, uint16_t data)
{
	if(type == COMMAND)
		_LCD_CONTROL_PORT &= ~(1 << _LCD_RS);
	else
		_LCD_CONTROL_PORT |= (1 << _LCD_RS);

	// Select
	_LCD_CONTROL_PORT &= ~(1 << _LCD_CS);

	#ifdef PARALLEL_MODE
		_LCD_HI_PORT = (data >> 8);
		_LCD_LO_PORT = data;
	#else
		#ifdef ENDIAN
			uint8_t a = data >> 8;
			data <<= 8;
			data |= a;
		#endif
		shift(data);
	#endif

	_LCD_CONTROL_PORT &= ~(1 << _LCD_WR);
	_LCD_CONTROL_PORT |= (1 << _LCD_WR);

	// Unselect
	_LCD_CONTROL_PORT |= (1 << _LCD_CS);
}

inline void SSD1289_WriteCommand(uint16_t address, uint16_t data)
{
	SSD1289_Write(COMMAND, address);
	SSD1289_Write(DATA, data);
}

void SSD1289_DisplayON(void)
{
	// Power supply setting
	SSD1289_WriteCommand(POWER_CONTROL_1, 0xA8A4);
	SSD1289_WriteCommand(POWER_CONTROL_2, 0x0000);
	SSD1289_WriteCommand(POWER_CONTROL_3, 0x000C);
	SSD1289_WriteCommand(POWER_CONTROL_4, 0x2B00);
	SSD1289_WriteCommand(POWER_CONTROL_5, 0x00B7);

	SSD1289_WriteCommand(DISPLAY_CONTROL, 0x0021);

	SSD1289_WriteCommand(OSCILATOR, 0x0001);

	SSD1289_WriteCommand(DISPLAY_CONTROL, 0x0023);

	// Exit sleep mode
	SSD1289_WriteCommand(SLEEP_MODE, 0x0000);
	_delay_ms(30);

	SSD1289_WriteCommand(DISPLAY_CONTROL, 0x0033);

	// Entry mode setting
	SSD1289_WriteCommand(ENTRY_MODE, 0x6070);

	// LCD driver AC setting
	SSD1289_WriteCommand(LCD_DRIVE_AC, 0x0600);

	SSD1289_WriteCommand(DRIVER_OUTPUT, 0x2B3F);
}

void SSD1289_SleepMode(void)
{
	SSD1289_WriteCommand(SLEEP_MODE, 0x0001);
}

void SSD1289_ReleaseFromSleep(void)
{
	SSD1289_WriteCommand(SLEEP_MODE, 0x0000);
}

void SSD1289_Init()
{
	// Configure IO
	_LCD_CONTROL_DDR |= (1 << _LCD_RS) |
						(1 << _LCD_WR) |
						(1 << _LCD_CS);

	#ifdef PARALLEL_MODE
		_LCD_HI_DDR = 0xFF;
		_LCD_LO_DDR = 0xFF;
	#else
		_SHIFT_DDR |= (1 << _SHIFT_DAT) | (1 << _SHIFT_CLK) | (1 << _SHIFT_LAT);
		_SHIFT_PORT &= ~((1 << _SHIFT_CLK) | (1 << _SHIFT_LAT) | (1 << _SHIFT_DAT));
	#endif

	#ifdef _LCD_RD
		_LCD_CONTROL_DDR |= (1 << _LCD_RD);
		_LCD_CONTROL_PORT |= (1 << _LCD_RD);
	#endif

	// Reset
	#ifdef _LCD_RESET
		_LCD_CONTROL_DDR |= (1 << _LCD_RESET);

		_LCD_CONTROL_PORT &= ~(1 << _LCD_RESET);
		_delay_ms(15);
		_LCD_CONTROL_PORT |= (1 << _LCD_RESET);
		_delay_ms(15);
	#endif

	SSD1289_DisplayON();
}

inline void SetCursor(uint16_t x, uint16_t y)
{
	SSD1289_WriteCommand(GDDRAM_X_ADDRESS_COUNTER, x);
	SSD1289_WriteCommand(GDDRAM_Y_ADDRESS_COUNTER, y);
}

void SetArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	SSD1289_WriteCommand(HORIZONTAL_RAM_POS, (y2 << 8) | y1);
	SSD1289_WriteCommand(VERTICAL_RAM_POS_START, x1);
	SSD1289_WriteCommand(VERTICAL_RAM_POS_END, x2);
	SetCursor(x1, y1);
}

inline void DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
	SetCursor(x, y);
	SSD1289_WriteCommand(RAM_DATA, color);
}

void DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
					uint16_t color)
{
	SetArea(x1, y1, x2, y2);
	SSD1289_WriteCommand(RAM_DATA, color);
	for(int y = y1; y <= y2; y++)
		for(int x = x1; x <= x2; x++)
		{
			_LCD_CONTROL_PORT &= ~(1 << _LCD_CS);
			_LCD_CONTROL_PORT &= ~(1 << _LCD_WR);
			_LCD_CONTROL_PORT |= (1 << _LCD_WR);
			_LCD_CONTROL_PORT |= (1 << _LCD_CS);
		}
}

void FillScreen(uint16_t color)
{
	DrawRectangle(0, 0, MAX_X, MAX_Y, color);
}
