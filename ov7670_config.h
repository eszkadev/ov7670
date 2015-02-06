/*
 * OV7670 + SSD1289 or UART
 * Author: Szymon Kłos
*/

// resolution
#define QQVGA
//#define QVGA

// show image on SSD1289 lcd - see config.h file (if commented, image is send by UART)
//#define WITH_LCD

// turn on test_pattern
#define test_pattern

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
