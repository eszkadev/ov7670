#ifndef _I2C_
#define _I2C_

/*
 * Author: Szymon Kłos
*/

#include "config.h"

#ifdef _PLATFORM_ATMEGA16
	#include "atmega16/twi.h"
	#include <avr/io.h>

	inline static void i2c_init(void) __attribute__((always_inline));
	inline static uint8_t i2c_write_reg(uint16_t addr, uint8_t reg, uint8_t data) __attribute__((always_inline));

	inline static void i2c_init(void)
	{
		twi_init();
	}

	inline static uint8_t i2c_write_reg(uint16_t addr, uint8_t reg, uint8_t data)
	{
		return write_reg(addr, reg, data);
	}
#endif

#endif
