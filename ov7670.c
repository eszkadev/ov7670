/*
 * OV7670 + SSD1289 or UART
 * Author: Szymon Kłos
*/

#include "ov7670.h"
#include "hardware/io.h"
#include "hardware/i2c.h"
#include "hardware/lcd.h"
#include "hardware/uart.h"
#include <util/delay.h>

void set_registers(void);

void OV7670_init(void)
{
	// IO PINS
	set_data_in();
	set_pclk_in();
	set_vsync_in();
	set_hsync_in();
	init_xclk();

	i2c_init();

	if(!i2c_write_reg(OV7670_W, 0x12, 0x80)); // reset the camera registers
	_delay_ms(200);

	i2c_write_reg(OV7670_W, REG_CLKRC, 0x3F); // frequency divider - 3F max

	set_registers();

	set_resolution(res_QQVGA);
	set_color(color_RGB565);
}

void set_resolution(uint8_t res)
{
	switch(res)
	{
		case res_QQVGA:
			i2c_write_reg(OV7670_W, REG_HSTART, 0x16);
			i2c_write_reg(OV7670_W, REG_HSTOP, 0x04);
			i2c_write_reg(OV7670_W, REG_HREF, 0x24);
			i2c_write_reg(OV7670_W, REG_VSTART, 0x02);
			i2c_write_reg(OV7670_W, REG_VSTOP, 0x7a);
			i2c_write_reg(OV7670_W, REG_VREF, 0x0a);
			i2c_write_reg(OV7670_W, REG_COM14, 0x1a);
			i2c_write_reg(OV7670_W, 0x72, 0x22);
			i2c_write_reg(OV7670_W, 0x73, 0xf2);
		break;

		case res_QVGA:
			i2c_write_reg(OV7670_W, REG_HSTART, 0x16);
			i2c_write_reg(OV7670_W, REG_HSTOP, 0x04);
			i2c_write_reg(OV7670_W, REG_HREF, 0x24);
			i2c_write_reg(OV7670_W, REG_VSTART, 0x02);
			i2c_write_reg(OV7670_W, REG_VSTOP, 0x7a);
			i2c_write_reg(OV7670_W, REG_VREF, 0x0a);
			i2c_write_reg(OV7670_W, REG_COM14, 0x19);
			i2c_write_reg(OV7670_W, 0x72, 0x11);
			i2c_write_reg(OV7670_W, 0x73, 0xf1);
		break;
	}
}

void set_color(uint8_t color)
{
	switch(color)
	{
		case color_RGB565:
			i2c_write_reg(OV7670_W, REG_COM7, 0x04); // RGB mode
			i2c_write_reg(OV7670_W, REG_COM15, 0xD0); // RGB565 full range
		break;
	}
}

void capture_image(uint16_t w, uint16_t h)
{
	uint8_t x = 0;
	uint8_t y = 0;

	y = 0;
	while(!get_vsync());
	while(y < h)
	{
		x = 0;
		while(!get_hsync());
		while(get_hsync())
		{
			while(!get_pclk());

			#ifdef WITH_LCD
				uint16_t color = ((uint16_t)get_data())<<8;
			#else
				uint8_t c = get_data();
				uart_put(c);
			#endif

			while(get_pclk());
			while(!get_pclk());

			#ifdef WITH_LCD
				color += get_data();
				if(x<200 && y<200)
				{
					draw_pixel(x, y, color);
				}
			#else
				c = get_data();
				uart_put(c);
				while(get_pclk());
				while(!get_pclk());

			#endif

			++x;
		}
		++y;
	}
}

void set_registers(void)
{
		i2c_write_reg(OV7670_W, REG_TSLB, 0x04);
		i2c_write_reg(OV7670_W, REG_COM3, 0x04);

		// test pattern
		i2c_write_reg(OV7670_W, 0x70, 0x4a);
		#ifdef test_pattern
			i2c_write_reg(OV7670_W, 0x71, 0x35 | (1<<7));
		#else
			i2c_write_reg(OV7670_W, 0x71, 0x35);
		#endif

		// colors
		i2c_write_reg(OV7670_W, MTX1, 0x80);
		i2c_write_reg(OV7670_W, MTX2, 0x80);
		i2c_write_reg(OV7670_W, MTX3, 0x00);
		i2c_write_reg(OV7670_W, MTX4, 0x22);
		i2c_write_reg(OV7670_W, MTX5, 0x5e);
		i2c_write_reg(OV7670_W, MTX6, 0x80);
		i2c_write_reg(OV7670_W, MTXS, 0x9e);
		i2c_write_reg(OV7670_W, AWBC7, 0x88);
		i2c_write_reg(OV7670_W, AWBC8, 0x88);
		i2c_write_reg(OV7670_W, AWBC9, 0x44);
		i2c_write_reg(OV7670_W, AWBC10, 0x67);
		i2c_write_reg(OV7670_W, AWBC11, 0x49);
		i2c_write_reg(OV7670_W, AWBC12, 0x0e);
		i2c_write_reg(OV7670_W, REG_GFIX, 0x00);
		i2c_write_reg(OV7670_W, AWBCTR3, 0x0a);
		i2c_write_reg(OV7670_W, AWBCTR2, 0x55);
		i2c_write_reg(OV7670_W, AWBCTR1, 0x11);
		i2c_write_reg(OV7670_W, AWBCTR0, 0x9f);

		i2c_write_reg(OV7670_W, REG_COM8, 0x8F); // AGC AWB AEC Unlimited step size
		i2c_write_reg(OV7670_W, 0xAA, 0x14);
		i2c_write_reg(OV7670_W, REG_BRIGHT, 0x00);
		i2c_write_reg(OV7670_W, REG_CONTRAS, 0x40);

		/*i2c_write_reg(OV7670_W, MTX1, 0xc0);
		i2c_write_reg(OV7670_W, MTX2, 0xc0);
		i2c_write_reg(OV7670_W, MTX3, 0x00);
		i2c_write_reg(OV7670_W, MTX4, 0x33);
		i2c_write_reg(OV7670_W, MTX5, 0x8d);
		i2c_write_reg(OV7670_W, MTX6, 0xc0);
		i2c_write_reg(OV7670_W, MTXS, 0x9e);*/
}
