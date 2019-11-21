#include "i2c.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

// I2C clock in 100kHz
#ifndef F_SCL
#define F_SCL  100000UL
#endif

I2C::I2C()
: _own_address(0)
{
	TWCR = (1<<TWEN);
	TWSR = 0; // prescaler value 1
	TWBR = (((F_CPU / F_SCL) - 16) / 8);
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
}

I2C::I2C(u8 own_address)
: _own_address(own_address)
{
	TWCR = (1<<TWEN);
	TWAR = (_own_address & 0x7F) << 1;
	TWSR = 0;
	TWBR = (((F_CPU / F_SCL) - 16) / 8);
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
}

I2C::~I2C()
{}

u8 I2C::set(u8 twi_address, u8 * twi_snd_buffer, u8 twi_nb_snd)
{
	return action(twi_address, twi_snd_buffer, twi_nb_snd, 0, 0);
}

u8 I2C::get(u8 twi_address, u8 * twi_rcv_buffer, u8 twi_nb_rcv)
{
	return action(twi_address, 0, 0, twi_snd_buffer, twi_nb_snd);
}
	
u8 I2C::action(
u8 twi_address,
u8 *twi_snd_buffer,
u8 twi_nb_snd,
u8 *twi_rcv_buffer,
u8 twi_nb_rcv)
{
	u8 i;
	u8 state;

	if (twi_nb_snd != 0)
	{
		TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
		if (0x08 != status())
		{
			TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
			return 1;
		}

		TWDR = twi_address;
		TWCR = (1<<TWINT) | (1<<TWEN);
		if (0x18 != status())
		{
			TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
			return 2;
		}

		i = 0;
		while (i<twi_nb_snd)
		{
			TWDR = twi_snd_buffer[i];
			TWCR = (1<<TWINT) | (1<<TWEN);
			if (0x28 != status())
			{
				TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
				return 4;
			}

			i++;
		}
	}

	if (twi_nb_rcv != 0)
	{
		TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
		state = status();
		if ((0x08 != state) && (0x10 != state))
		{
			TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
			return 8;
		}

		TWDR = twi_address|1;
		TWCR = (1<<TWINT) | (1<<TWEN);
		if (0x40 != status())
		{
			TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
			return 16;
		}

		memset (twi_rcv_buffer, 0, twi_nb_rcv);

		i = 0;
		while (i<twi_nb_rcv-1)
		{
			TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
			if (0x50 != status())
			{
				TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
				return 32;
			}
			twi_rcv_buffer[i] = TWDR;

			i++;
		}

		TWCR = (1<<TWINT) | (1<<TWEN);
		if (0x58 != status())
		{
			TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
			return 64;
		}
		twi_rcv_buffer[i] = TWDR;
		i++;
	}

	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
	while(TWCR & (1<<TWSTO));

	return 0;
}

u8 I2C::status ()
{
	// attendre la fin du transfert
	while (!(TWCR & (1<<TWINT)));
	// lecture du resultat
	return (TWSR & 0xF8);
}
