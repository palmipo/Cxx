#include "raspispi.h"
#include "spiexception.h"
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <iomanip>

RaspiSPI::RaspiSPI(const std::string & device)
: CtrlSPI()
{
	_handler = open(device.c_str(), O_RDWR);
	if (_handler < 0)
		throw SPIException("SPI::SPI()");
}

RaspiSPI::~RaspiSPI()
{
	close(_handler);
}

/*
#define SPI_CPHA		0x01
#define SPI_CPOL		0x02

#define SPI_MODE_0		(0|0)
#define SPI_MODE_1		(0|SPI_CPHA)
#define SPI_MODE_2		(SPI_CPOL|0)
#define SPI_MODE_3		(SPI_CPOL|SPI_CPHA)

#define SPI_CS_HIGH		0x04
#define SPI_LSB_FIRST		0x08
#define SPI_3WIRE		0x10
#define SPI_LOOP		0x20
#define SPI_NO_CS		0x40
#define SPI_READY		0x80
*/
void RaspiSPI::setMode(uint32_t mode)
{
	if (ioctl(_handler, SPI_IOC_WR_MODE, (uint32_t*)&mode) < 0)
		throw SPIException("RaspiSPI::setMode()");
	if (ioctl(_handler, SPI_IOC_RD_MODE, (uint32_t*)&mode) < 0)
		throw SPIException("RaspiSPI::setMode()");
}


void RaspiSPI::setClockRate(uint32_t speed)
{
	_speed = speed;
	if (ioctl (_handler, SPI_IOC_WR_MAX_SPEED_HZ, (uint32_t*)&_speed) < 0)
		throw SPIException("RaspiSPI::setClockRate()");
	if (ioctl (_handler, SPI_IOC_RD_MAX_SPEED_HZ, (uint32_t*)&_speed) < 0)
		throw SPIException("RaspiSPI::setClockRate()");
}


void RaspiSPI::setBitPerWord(uint32_t order)
{
	_bit_per_word = order;
	if (ioctl (_handler, SPI_IOC_WR_BITS_PER_WORD, (uint32_t*)&_bit_per_word) < 0)
		throw SPIException("RaspiSPI::setBitPerWord()");
	if (ioctl (_handler, SPI_IOC_RD_BITS_PER_WORD, (uint32_t*)&_bit_per_word) < 0)
		throw SPIException("RaspiSPI::setBitPerWord()");
}


void RaspiSPI::set(uint8_t * cmd, int32_t length)
{
	std::cout << "spi out (" << length << ") : " << std::hex;
	for (uint32_t i=0; i<length; i+=1)
	{
		std::cout << (int)cmd[i] << " ";
	}
	std::cout << std::dec << std::endl;
	
	transfer(cmd, 0, length);
}


void RaspiSPI::get(uint8_t * rcv, int32_t length)
{
	transfer(0, rcv, length);
}


void RaspiSPI::transfer(uint8_t * cmd, uint8_t * rcv, int32_t length)
{
	struct spi_ioc_transfer io;
	memset(&io, 0, sizeof(struct spi_ioc_transfer));
	io.tx_buf = (unsigned long long)cmd;
	io.rx_buf = (unsigned long long)rcv;
	io.len = length;
	io.speed_hz = _speed;
	io.delay_usecs = 0; //100;
	io.bits_per_word = _bit_per_word;
	// io.cs_change = 0;
	// io.tx_nbits = 0;
	// io.rx_nbits = 0;
	// io.pad = 0;

	if (ioctl (_handler, SPI_IOC_MESSAGE(1), &io) < 0)
		throw SPIException("RaspiSPI::transfer()");
}
