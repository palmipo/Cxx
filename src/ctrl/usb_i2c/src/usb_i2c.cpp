#include "usb_i2c.h"
#include "i2cexception.h"
#include "rs232.h"
#include "tempo.h"
#include <iostream>

/*
Command
Value
Description
Available in I2C-USB Version

I2C_SGL
0x53
Read/Write single byte for non-registered devices, such as the Philips PCF8574 I/O chip.
All

I2C_AD1
0x55
Read/Write single or multiple bytes for 1 byte addressed devices (the majority of devices will use this one)
All

I2C_USB
0x5A
A range of commands to the USB-I2C module, generally to improve selected communications or provide analogue/digital I/O
All
*/
UsbI2C::UsbI2C(RS232 * serial)
: CtrlI2C()
, _uart(serial)
{
	_uart->setConfig(B19200, 8, 'N', 2, 0);
	_uart->setInterCharacterTimer(50);
}

uint8_t UsbI2C::getVersion()
{
	uint8_t version = 0;
	uint8_t cmd[4] = { 0x5A, 0x01, 0, 0 };
	std::cout << (int)_uart->write(cmd, 4) << std::endl;
	std::cout << (int)_uart->read(&version, 1) << std::endl;
	Tempo::millisecondes(500);
	
	return version;
}

void UsbI2C::setOwnAddress(uint8_t own_address)
{}

void UsbI2C::set (uint8_t addr, uint8_t* buf, int32_t len)
{
	if (len == 1)
	{
		int32_t length = 3;
		uint8_t msg[length];
		msg[0] = 0x53;
		msg[1] = addr<<1;
		msg[2] = buf[0];

		std::cout << (int)_uart->write(msg, length) << std::endl;
		Tempo::millisecondes(500);
	}
	else
	{
		int32_t length = 3 + len;
		uint8_t msg[length];
		msg[0] = 0x55;
		msg[1] = addr<<1;
		msg[2] = buf[0];
		msg[3] = len-1;
		for (int32_t i=1; i<len; i+=1)
		{
			msg[3+i] = buf[i];
		}

		std::cout << (int)_uart->write(msg, length) << std::endl;
		Tempo::millisecondes(500);
	}
}

void UsbI2C::get (uint8_t addr, uint8_t* buf, int32_t len)
{
	if (len == 1)
	{
		int32_t length = 2;
		uint8_t msg[length];
		msg[0] = 0x53;
		msg[1] = (addr<<1)|1;

		std::cout << (int)_uart->write(msg, length) << std::endl;
		std::cout << (int)_uart->read(buf, 1) << std::endl;
		Tempo::millisecondes(500);
	}
	else
	{
		int32_t length = 4;
		uint8_t msg[length];
		msg[0] = 0x55;
		msg[1] = (addr<<1)|1;
		msg[2] = 0;
		msg[3] = len;

		std::cout << (int)_uart->write(msg, length) << std::endl;
		std::cout << (int)_uart->read(buf, len) << std::endl;
		Tempo::millisecondes(500);
	}
}

void UsbI2C::transfer (uint8_t addr, uint8_t* cmd, int32_t cmd_len, uint8_t* buf, int32_t buf_len)
{
	set(addr, cmd, cmd_len);
	get(addr, buf, buf_len);
}
