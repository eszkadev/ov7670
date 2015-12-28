/*
 * OV7670 + SSD1289 or UART
 * Author: Szymon Kłos
*/

#include "ov7670_config.h"
#include <avr/io.h>

#define res_QQVGA 0
#define res_QVGA 1

#define color_RGB565 0

void OV7670_init(void);
void set_resolution(uint8_t res);
void set_color(uint8_t color);
void capture_image(uint16_t w, uint16_t h);



#define OV7670_W	0x42
#define OV7670_R	0x43

#define REG_GAIN	0x00
#define REG_BLUE	0x01
#define REG_RED		0x02
#define REG_VREF	0x03
#define REG_COM1	0x04
#define REG_BAVE	0x05
#define REG_GbAVE	0x06
#define REG_AECHH	0x07
#define REG_RAVE	0x08
#define REG_COM2	0x09
#define REG_PID		0x0a
#define REG_VER		0x0b
#define REG_COM3	0x0c
#define REG_COM4	0x0d
#define REG_COM5	0x0e
#define REG_COM6	0x0f
#define REG_AECH	0x10
#define REG_CLKRC	0x11
#define REG_COM7	0x12
#define REG_COM8	0x13
#define REG_COM9	0x14
#define REG_COM10	0x15
#define REG_HSTART	0x17
#define REG_HSTOP	0x18
#define REG_VSTART	0x19
#define REG_VSTOP	0x1a
#define REG_PSHFT	0x1b
#define REG_MIDH	0x1c
#define REG_MIDL	0x1d
#define REG_MVFP	0x1e
#define REG_AEW		0x24
#define REG_AEB		0x25
#define REG_VPT		0x26
#define REG_HSYST	0x30
#define REG_HSYEN	0x31
#define REG_HREF	0x32
#define REG_TSLB	0x3a
#define REG_COM11	0x3b
#define REG_COM12	0x3c
#define REG_COM13	0x3d
#define REG_COM14	0x3e
#define REG_EDGE	0x3f
#define REG_COM15	0x40
#define REG_COM16	0x41
#define REG_COM17	0x42
#define MTX1		0x4f
#define MTX2		0x50
#define MTX3		0x51
#define MTX4		0x52
#define MTX5		0x53
#define MTX6		0x54
#define REG_BRIGHT	0x55
#define REG_CONTRAS	0x56
#define MTXS		0x58
#define AWBC7		0x59
#define AWBC8		0x5a
#define AWBC9		0x5b
#define AWBC10		0x5c
#define AWBC11		0x5d
#define AWBC12		0x5e
#define REG_GFIX    0x69
#define GGAIN		0x6a
#define DBLV		0x6b
#define AWBCTR3		0x6c
#define AWBCTR2		0x6d
#define AWBCTR1		0x6e
#define AWBCTR0		0x6f
