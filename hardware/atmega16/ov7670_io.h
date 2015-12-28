#ifndef _ATMEGA16_OV7670_IO_
#define _ATMEGA16_OV7670_IO_

/*
 * Author: Szymon Kłos
*/

#include <avr/io.h>

// IO PINS

#define XCLK PD7 // PWM
#define XCLK_DDR DDRD

#define PCLK PC7
#define PCLK_DDR DDRC
#define PCLK_PIN PINC

#define VSYNC PC6
#define VSYNC_DDR DDRC
#define VSYNC_PIN PINC

#define HSYNC PC5
#define HSYNC_DDR DDRC
#define HSYNC_PIN PINC

#define DATA_PIN PINA
#define DATA_DDR DDRA

inline static void set_data_in(void) __attribute__((always_inline));
inline static uint8_t get_data(void) __attribute__((always_inline));
inline static void set_pclk_in(void) __attribute__((always_inline));
inline static uint8_t get_pclk(void) __attribute__((always_inline));
inline static void set_vsync_in(void) __attribute__((always_inline));
inline static uint8_t get_vsync(void) __attribute__((always_inline));
inline static void set_hsync_in(void) __attribute__((always_inline));
inline static uint8_t get_hsync(void) __attribute__((always_inline));
inline static void init_xclk(void) __attribute__((always_inline));

inline static void set_data_in(void)
{
	DATA_DDR = 0x00;
}

inline static uint8_t get_data(void)
{
	return DATA_PIN;
}

inline static void set_pclk_in(void)
{
	PCLK_DDR &= ~(1 << PCLK);
}

inline static uint8_t get_pclk(void)
{
	return PCLK_PIN & (1 << PCLK);
}

inline static void set_vsync_in(void)
{
	VSYNC_DDR &= ~(1 << VSYNC);
}

inline static uint8_t get_vsync(void)
{
	return VSYNC_PIN & (1 << VSYNC);
}

inline static void set_hsync_in(void)
{
	HSYNC_DDR &= ~(1 << HSYNC);
}

inline static uint8_t get_hsync(void)
{
	return HSYNC_PIN & (1 << HSYNC);
}

inline static void init_xclk(void)
{
	// XCLK 8 MHz
	XCLK_DDR |= (1 << XCLK);
	TCNT2 = 0;
	OCR2 = 1;
	TCCR2 = (1<<WGM21) | (1<<COM20) | (1<<CS20);
}

#endif
