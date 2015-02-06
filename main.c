/*
 * OV7670 + SSD1289 or UART
 * Author: Szymon Kłos
 *
 * Atmega16 with 16 MHz crystal oscillator requied !!!
 * You should power MCU and camera with 3,3V.
 * SDA and SCL connect by resistor to VCC.
 *
 * You can receive the image on the PC using my tool: https://github.com/sk94/cam_capture
 *
*/

#include <avr/io.h>
#include "twi.h"
#include "ov7670.h"
#include "ssd1289.h"
#include "uart.h"

// To turn off test pattern comment the test_pattern definition in ov7670_config.h

int main()
{
	#ifdef WITH_LCD
		SSD1289_Init();
		FillScreen(RGB(0, 0, 0));
	#else
		uart_init(B115200);
	#endif

	OV7670_init();

	while(1)
	{
		#ifndef WITH_LCD
			uart_put_string("START");
		#endif

		#ifdef QVGA
			capture_image(320, 240);
		#elif defined QQVGA
			capture_image(160, 120);
		#elif defined VGA
			capture_image(640, 480);
		#endif

		#ifndef WITH_LCD
			uart_put_string("STOP");
		#endif
	}

	return 0;
}
