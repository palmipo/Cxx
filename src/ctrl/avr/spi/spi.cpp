#include "spi.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

void (*_spi_callback)(unsigned char);

ISR(SPI_STC_vect)
{
	cli();
	if (!(SPSR & (1<<WCOL)))
	{
		if (_spi_callback != 0)
		{
			_spi_callback(SPDR);
		}
	}
	sei();
}

/*
PB7 SCK  (SPI Bus Serial Clock)
PB6 MISO (SPI Bus Master Input/Slave Output)
PB5 MOSI (SPI Bus Master Output/Slave Input)
PB4 _SS  (SPI Slave Select Input)
*/
SPI::SPI()
{
	_spi_callback = 0;

/*
	setMaster();
	setSlave();
	setMode(0);
	setClockRate(4);
	setDataOrder(0);
*/
}

SPI::~SPI()
{
	SPCR = 0;
}

void SPI::setMaster()
{
	// Set MOSI, SCK, _SS output ; MISO input
	unsigned char mask1 = DDRB & ~((1<<PB7) | (1<<PB6) | (1<<PB5) | (1<<PB4));
	DDRB = mask1 | (1<<PB7) | (1<<PB5) | (1<<PB4);

	// _SS = HIGH
	unsigned char mask2 = PORTB & ~(1<<PB4);
	PORTB = mask2 | (1<<PB4);

	// Enable SPI
	SPCR = (1 << SPIE) | (1<<SPE) | (1<<MSTR);

	unsigned char tmp1 = SPSR;
	unsigned char tmp2 = SPDR;
}

void SPI::setSlave()
{
	/* Set MISO output ; MOSI, SCK, _SS input */
	unsigned char mask1 = DDRB & ~((1<<PB7) | (1<<PB6) | (1<<PB5) | (1<<PB4));
	DDRB = mask1 | (1<<PB6);

	/* Enable SPI */
	SPCR = (1 << SPIE) | (1<<SPE);

	unsigned char tmp1 = SPSR;
	unsigned char tmp2 = SPDR;
}

void SPI::setMode(unsigned char mode)
{
	unsigned char mask = SPCR & ~((1<<CPOL) | (1<<CPHA));
	switch(mode)
	{
		case 1:
		SPCR = mask | (1<<CPHA);
		break;

		case 2:
		SPCR = mask | (1<<CPOL);
		break;

		case 3:
		SPCR = mask | ((1<<CPOL) | (1<<CPHA));
		break;

		default:
		SPCR = mask;
		break;
	}
}

void SPI::setClockRate(unsigned char rate)
{
	unsigned char mask = SPCR & ~((1<<SPR1) | (1<<SPR0));
	switch(rate)
	{
		case 4:
		SPCR = mask;
		SPSR = 0;
		break;
		case 16:
		SPCR = mask | (1<<SPR0);
		SPSR = 0;
		break;
		case 64:
		SPCR = mask | (1<<SPR1);
		SPSR = 0;
		break;
		case 256:
		SPCR = mask | (1<<SPR1) | (1<<SPR0);
		SPSR = 0;
		break;
		case 2:
		SPCR = mask;
		SPSR = (1<<SPI2X);
		break;
		case 8:
		SPCR = mask | (1<<SPR0);
		SPSR = (1<<SPI2X);
		break;
		case 32:
		SPCR = mask | (1<<SPR1);
		SPSR = (1<<SPI2X);
		break;
		case 128:
		SPCR = mask | (1<<SPR1) | (1<<SPR0);
		SPSR = (1<<SPI2X);
		break;
		default:
		SPCR = mask;
		SPSR = 0;
		break;
	}
}

void SPI::setDataOrder(unsigned char order)
{
	unsigned char mask = SPCR & ~(1<<DORD);
	SPCR = mask | (order<<DORD);
}

void SPI::send(unsigned char * buffer, unsigned char length)
{
	cli();
	unsigned char i=0;
	while ((i<length) && (!(SPSR & (1<<WCOL))))
	{
		SPDR = buffer[i];
		while(!(SPSR & (1<<SPIF)));
		i++;
	}
	sei();
}

void SPI::recv(unsigned char * buffer, unsigned char length)
{
	cli();
	unsigned char i=0;
	while ((i<length) && (!(SPSR & (1<<WCOL))))
	{
		while(!(SPSR & (1<<SPIF)));
		buffer[i] = SPDR;
		i++;
	}
	sei();
}

void SPI::setRecvCallback(void (*callback)(unsigned char))
{
	_spi_callback = callback;
}
