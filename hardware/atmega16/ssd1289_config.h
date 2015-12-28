/*
 * SSD1289
 * Author: Szymon Kłos
*/

#define MAX_X 319
#define MAX_Y 239
//#define PARALLEL_MODE 1
#define ENDIAN 1
#define HORIZONTAL 1

// Control port

#define _LCD_CONTROL_PORT PORTB
#define _LCD_CONTROL_DDR  DDRB
#define _LCD_RS           PB0
#define _LCD_WR           PB1
//#define _LCD_RD           PB2 // if not used RD -> VCC
#define _LCD_CS           PB3
//#define _LCD_RESET        PB4 // if not used RESET -> VCC

// Data ports (parallel mode)

#ifdef PARALLEL_MODE

#define _LCD_HI_PORT      PORTA
#define _LCD_HI_DDR       DDRA
#define _LCD_HI_PIN       PINA

#define _LCD_LO_PORT      PORTD
#define _LCD_LO_DDR       DDRD
#define _LCD_LO_PIN       PIND

#else

#define _SHIFT_PORT   PORTD
#define _SHIFT_DDR    DDRD
#define _SHIFT_PIN    PIND

#define _SHIFT_DAT    PD2
#define _SHIFT_CLK    PD3
#define _SHIFT_LAT    PD4

#endif

// Touch port

#define _TOUCH_PORT       PORTC
#define _TOUCH_DDR        DDRC
#define _TOUCH_DCLK       PC0
#define _TOUCH_CS         PC3
#define _TOUCH_IN         PC1
#define _TOUCH_BUSY       PC2
#define _TOUCH_OUT        PC7
#define _TOUCH_IRQ        PC6

// SSD1289 Registers

#define OSCILATOR                  0x00
#define DRIVER_OUTPUT              0x01
#define LCD_DRIVE_AC               0x02
#define POWER_CONTROL_1            0x03
#define COMPARE_REGISTER_1         0x05
#define COMPARE_REGISTER_2         0x06
#define DISPLAY_CONTROL            0x07
#define FRAME_CYCLE_CONTROL        0x0B
#define POWER_CONTROL_2            0x0C
#define POWER_CONTROL_3            0x0D
#define POWER_CONTROL_4            0x0E
#define GATE_SCAN_START_POS        0x0F
#define SLEEP_MODE                 0x10
#define ENTRY_MODE                 0x11
#define OPTIM_ACCESS_SPPED3        0x12
#define GENERIC_INTERFACE_CTRL     0x15
#define HORIZONTAL_PORCH           0x16
#define VERTICAL_PORCH             0x17
#define POWER_CONTROL_5            0x1E
#define RAM_DATA                   0x22
#define RAM_WRITE_MASK_1           0x23
#define RAM_WRITE_MASK_2           0x24
#define FRAME_FREQ                 0x25
#define GAMMA_1                    0x30
#define GAMMA_2                    0x31
#define GAMMA_3                    0x32
#define GAMMA_4                    0x33
#define GAMMA_5                    0x34
#define GAMMA_6                    0x35
#define GAMMA_7                    0x36
#define GAMMA_8                    0x37
#define GAMMA_9                    0x3A
#define GAMMA_10                   0x3B
#define VERTICAL_SCROLL_1          0x41
#define VERTICAL_SCROLL_2          0x42
#define HORIZONTAL_RAM_POS         0x44
#define VERTICAL_RAM_POS_START     0x45
#define VERTICAL_RAM_POS_END       0x46
#define FIRST_WINDOW_START         0x48
#define FIRST_WINDOW_END           0x49
#define SECOND_WINDOW_START        0x4A
#define SECOND_WINDOW_END          0x4B
#define GDDRAM_X_ADDRESS_COUNTER   0x4E
#define GDDRAM_Y_ADDRESS_COUNTER   0x4F
