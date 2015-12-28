/*
 * SSD1289
 * Author: Szymon Kłos
*/

#ifndef _SHIFT_
#define _SHIFT_

#include <avr/io.h>
#include <util/delay.h>
#include "ssd1289_config.h"

void shift(uint16_t data);

#endif
