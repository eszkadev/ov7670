/*
 * OV7670 + SSD1289 or UART
 * Author: Szymon Kłos
*/

#include "ov7670.h"

void set_registers(void);

void OV7670_init(void)
{
	// IO PINS
	DATA_DDR = 0x00;
	PCLK_DDR &= ~(1 << PCLK);
	VSYNC_DDR &= ~(1 << VSYNC);
	HSYNC_DDR &= ~(1 << HSYNC);

	// XCLK 8 MHz
	XCLK_DDR |= (1 << XCLK);
	TCNT2 = 0;
	OCR2 = 1;
	TCCR2 = (1<<WGM21) | (1<<COM20) | (1<<CS20);

	twi_init();

	if(!write_reg(OV7670_W, 0x12, 0x80)); // reset the camera registers
	_delay_ms(200);

	write_reg(OV7670_W, REG_CLKRC, 0x3F); // frequency divider - 3F max

	set_registers();

	set_resolution(res_QQVGA);
	set_color(color_RGB565);
}

void set_resolution(uint8_t res)
{
	switch(res)
	{
		case res_QQVGA:
			write_reg(OV7670_W, REG_HSTART, 0x16);
			write_reg(OV7670_W, REG_HSTOP, 0x04);
			write_reg(OV7670_W, REG_HREF, 0x24);
			write_reg(OV7670_W, REG_VSTART, 0x02);
			write_reg(OV7670_W, REG_VSTOP, 0x7a);
			write_reg(OV7670_W, REG_VREF, 0x0a);
			write_reg(OV7670_W, REG_COM14, 0x1a);
			write_reg(OV7670_W, 0x72, 0x22);
			write_reg(OV7670_W, 0x73, 0xf2);
		break;

		case res_QVGA:
			write_reg(OV7670_W, REG_HSTART, 0x16);
			write_reg(OV7670_W, REG_HSTOP, 0x04);
			write_reg(OV7670_W, REG_HREF, 0x24);
			write_reg(OV7670_W, REG_VSTART, 0x02);
			write_reg(OV7670_W, REG_VSTOP, 0x7a);
			write_reg(OV7670_W, REG_VREF, 0x0a);
			write_reg(OV7670_W, REG_COM14, 0x19);
			write_reg(OV7670_W, 0x72, 0x11);
			write_reg(OV7670_W, 0x73, 0xf1);
		break;
	}
}

void set_color(uint8_t color)
{
	switch(color)
	{
		case color_RGB565:
			write_reg(OV7670_W, REG_COM7, 0x04); // RGB mode
			write_reg(OV7670_W, REG_COM15, 0xD0); // RGB565 full range
		break;
	}
}

void capture_image(uint16_t w, uint16_t h)
{
	uint8_t x = 0;
	uint8_t y = 0;
	uint16_t color = 0;
	uint8_t c = 0;

	y = 0;
	while(!(VSYNC_PIN & (1<<VSYNC)));
	while(y < h)
	{
		x = 0;
		while(!(HSYNC_PIN & (1<<HSYNC)));
		while((HSYNC_PIN & (1<<HSYNC)))
		{
			while(!(PCLK_PIN & (1<<PCLK)));

			#ifdef WITH_LCD
				color = ((uint16_t)DATA_PIN)<<8;
			#else
				c = DATA_PIN;
				while(!( UCSRA & (1<<UDRE)));
				UDR = c;
			#endif

			while((PCLK_PIN & (1<<PCLK)));
			while(!(PCLK_PIN & (1<<PCLK)));

			#ifdef WITH_LCD
				color += (DATA_PIN);
				if(x<200 && y<200)
				{
					DrawPixel(x, y, color);
				}
			#else
				c = DATA_PIN;
				while(!(UCSRA & (1<<UDRE)));
				UDR = c;
				while((PCLK_PIN & (1<<PCLK)));
				while(!(PCLK_PIN & (1<<PCLK)));

			#endif

			++x;
		}
		++y;
	}
}

void set_registers(void)
{
		write_reg(OV7670_W, REG_TSLB, 0x04);
		write_reg(OV7670_W, REG_COM3, 0x04);

		// test pattern
		write_reg(OV7670_W, 0x70, 0x4a);
		#ifdef test_pattern
			write_reg(OV7670_W, 0x71, 0x35 | (1<<7));
		#else
			write_reg(OV7670_W, 0x71, 0x35);
		#endif

		// colors
		write_reg(OV7670_W, MTX1, 0x80);
		write_reg(OV7670_W, MTX2, 0x80);
		write_reg(OV7670_W, MTX3, 0x00);
		write_reg(OV7670_W, MTX4, 0x22);
		write_reg(OV7670_W, MTX5, 0x5e);
		write_reg(OV7670_W, MTX6, 0x80);
		write_reg(OV7670_W, MTXS, 0x9e);
		write_reg(OV7670_W, AWBC7, 0x88);
		write_reg(OV7670_W, AWBC8, 0x88);
		write_reg(OV7670_W, AWBC9, 0x44);
		write_reg(OV7670_W, AWBC10, 0x67);
		write_reg(OV7670_W, AWBC11, 0x49);
		write_reg(OV7670_W, AWBC12, 0x0e);
		write_reg(OV7670_W, REG_GFIX, 0x00);
		write_reg(OV7670_W, AWBCTR3, 0x0a);
		write_reg(OV7670_W, AWBCTR2, 0x55);
		write_reg(OV7670_W, AWBCTR1, 0x11);
		write_reg(OV7670_W, AWBCTR0, 0x9f);

		write_reg(OV7670_W, REG_COM8, 0x8F); // AGC AWB AEC Unlimited step size
		write_reg(OV7670_W, 0xAA, 0x14);
		write_reg(OV7670_W, REG_BRIGHT, 0x00);
		write_reg(OV7670_W, REG_CONTRAS, 0x40);

		/*write_reg(OV7670_W, MTX1, 0xc0);
		write_reg(OV7670_W, MTX2, 0xc0);
		write_reg(OV7670_W, MTX3, 0x00);
		write_reg(OV7670_W, MTX4, 0x33);
		write_reg(OV7670_W, MTX5, 0x8d);
		write_reg(OV7670_W, MTX6, 0xc0);
		write_reg(OV7670_W, MTXS, 0x9e);*/
}
