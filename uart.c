#include "uart.h"

static void uart_9600(void)
{
	#define BAUD 9600
	#include <util/setbaud.h>

	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;

	#if USE_2X
		UCSRA |= (1 << U2X);
	#else
		UCSRA &= ~(1 << U2X);
	#endif
}

static void uart_57600(void)
{
	#undef BAUD
	#define BAUD 57600
	#include <util/setbaud.h>

	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;

	#if USE_2X
		UCSRA |= (1 << U2X);
	#else
		UCSRA &= ~(1 << U2X);
	#endif
}

static void uart_115200(void)
{
	#undef BAUD
	#define BAUD 115200
	#include <util/setbaud.h>

	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;

	#if USE_2X
		UCSRA |= (1 << U2X);
	#else
		UCSRA &= ~(1 << U2X);
	#endif
}

void uart_init(int baud)
{
	switch(baud)
	{
		case B9600:
			uart_9600();
		break;

		case B57600:
			uart_57600();
		break;

		case B115200:
			uart_115200();
		break;

		default:
			uart_9600();
		break;
	}
	
	// setting frame
	// 8bit, 1bit stop
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
	
	// enabling rx and tx
	UCSRB = (1 << RXEN) | (1 << TXEN);
}

uint8_t uart_data_ready(void)
{
	return (UCSRA & (1 << RXC));
}

char uart_get(void)
{
	while(!uart_data_ready());
	return UDR;
}

void uart_put(char data)
{
	while (!(UCSRA & (1 << UDRE)));
	UDR = data;
}

void uart_put_string(char * data)
{
	unsigned int i = 0;
	while(data[i] != 0)
	{
		uart_put(data[i]);
		i++;
	}
}
