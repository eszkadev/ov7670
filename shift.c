/*
 * SSD1289
 * Author: Szymon Kłos
*/

#include "shift.h"

void shift(uint16_t data)
{
	uint16_t pos =  1 << 15;

	while(pos)
	{
		if(pos & data)
			_SHIFT_PORT |= (1 << _SHIFT_DAT);
		else
			_SHIFT_PORT &= ~(1 << _SHIFT_DAT);

		_SHIFT_PORT |= (1 << _SHIFT_CLK);
		_SHIFT_PORT &= ~(1 << _SHIFT_CLK);

		pos >>= 1;
	}

	_SHIFT_PORT |= (1 << _SHIFT_LAT);
	_SHIFT_PORT &= ~(1 << _SHIFT_LAT);
}
