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

#include "ov7670.h"

#ifdef WITH_LCD
	#include "hardware/lcd.h"
#else
	#include "hardware/uart.h"
#endif

// To turn off test pattern comment the test_pattern definition in ov7670_config.h

int main(void)
{
	#ifdef WITH_LCD
		lcd_init();
	#else
		uart_init(B115200);
	#endif

	OV7670_init();

	while(1)
	{
		#ifndef WITH_LCD
			// Magic numbers (sync signal)
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
