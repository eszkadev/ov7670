#ifndef _UART_H_
#define _UART_H_

#include <avr/io.h>

#define B9600 0
#define B115200 1
#define B57600 2

void uart_init(int baud);
uint8_t uart_data_ready(void);
char uart_get(void);
void uart_put(uint8_t data);
void uart_put_string(char * data);

#endif
