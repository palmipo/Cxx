#include "spi.h"
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

SPI::SPI(const std::string & device)
{
	_fd = open(device.c_str(), O_RDWR);
	if (_fd < 0)
		throw SPIException("SPI::SPI()");
}

SPI::~SPI()
{
	close(_fd);
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
void SPI::setMode(uint32_t mode)
{
	if (ioctl(_fd, SPI_IOC_WR_MODE, (uint32_t*)&mode) < 0)
		throw SPIException("SPI::setMode()");
	if (ioctl(_fd, SPI_IOC_RD_MODE, (uint32_t*)&mode) < 0)
		throw SPIException("SPI::setMode()");
}


void SPI::setClockRate(uint32_t speed)
{
	_speed = speed;
	if (ioctl (_fd, SPI_IOC_WR_MAX_SPEED_HZ, (uint32_t*)&_speed) < 0)
		throw SPIException("SPI::setClockRate()");
	if (ioctl (_fd, SPI_IOC_RD_MAX_SPEED_HZ, (uint32_t*)&_speed) < 0)
		throw SPIException("SPI::setClockRate()");
}


void SPI::setBitPerWord(uint32_t order)
{
	_bit_per_word = order;
	if (ioctl (_fd, SPI_IOC_WR_BITS_PER_WORD, (uint32_t*)&_bit_per_word) < 0)
		throw SPIException("SPI::setBitPerWord()");
	if (ioctl (_fd, SPI_IOC_RD_BITS_PER_WORD, (uint32_t*)&_bit_per_word) < 0)
		throw SPIException("SPI::setBitPerWord()");
}


void SPI::set(uint8_t * cmd, uint32_t length)
{
	std::cout << "spi out (" << length << ") : " << std::hex;
	for (uint32_t i=0; i<length; i+=1)
	{
		std::cout << (int)cmd[i] << " ";
	}
	std::cout << std::dec << std::endl;
	
	transfer(cmd, 0, length);
}


void SPI::get(uint8_t * rcv, uint32_t length)
{
	transfer(0, rcv, length);
}


void SPI::transfer(uint8_t * cmd, uint8_t * rcv, uint32_t length)
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

	if (ioctl (_fd, SPI_IOC_MESSAGE(1), &io) < 0)
		throw SPIException("SPI::transfer()");
}
