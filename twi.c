#include "twi.h"

void twi_init(void)
{
	DDRC &= ~((1 << PC4) | (1 << PC5));

	// SCL freq = CPU freq / (16 + 2*TWBR * 4^TWPS)
	// SCL freq = 16 000 000 Hz / (16 + 2*72 * 1) = 100 kHz

	TWSR &= ~3; // TWPS = 0
	TWBR = 72;
	// TWBR = ((F_CPU / SCL_CLOCK) - 16)/2;
}

uint8_t twi_start(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	while(!(TWCR & (1 << TWINT)));

	if((TWSR & 0xF8) != TW_START)
		return 0;

	return 1;
}

void twi_stop(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

	while ((TWCR & (1 << TWSTO)));

	_delay_ms(1);
}

uint8_t twi_write_addres(uint8_t addres, uint8_t ack)
{
	TWDR = addres;
	TWCR = (1 << TWINT) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)));

	if ((ack == ACK) && (TWSR & 0xF8) != TW_MT_SLA_ACK)
		return 0;

	return 1;
}

uint8_t twi_write_byte(uint8_t data, uint8_t ack)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)));

	if ((ack == ACK) && (TWSR & 0xF8) != TW_MT_DATA_ACK)
		return 0;

	return 1;
}

uint8_t twi_read_byte(uint8_t data, uint8_t ack)
{
	TWCR = ((ack == ACK)
	? ((1 << TWINT) | (1 << TWEN) | (1 << TWEA)) 
	: ((1 << TWINT) | (1 << TWEN))) ;

	while(!(TWCR & (1 << TWINT)));

	if(ack == ACK)
	{
		if((TWSR & 0xF8) != TW_MR_DATA_NACK)
		{
			return 0;
		}
	}
	else
	{
		if((TWSR & 0xF8) != TW_MR_DATA_ACK)
		{
			return 0;
		}
	}

	data = TWDR;

	return 1;
}

uint8_t write_reg(uint16_t addr, uint8_t reg, uint8_t dat)
{
	twi_start();

	if(twi_write_addres(addr, ACK))
		if(twi_write_byte(reg, ACK))
			if(twi_write_byte(dat, ACK))
			{
				twi_stop();
				return 1;
			}

	twi_stop();

	return 0;
}
