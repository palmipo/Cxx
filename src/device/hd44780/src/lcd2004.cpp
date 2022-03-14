#include "lcd2004.h"
#include "pcf8574at.h"
#include "tempo.h"
#include <iostream>

const uint8_t DB7  = 7;
const uint8_t DB6  = 6;
const uint8_t DB5  = 5;
const uint8_t DB4  = 4;
const uint8_t BLUE = 3;
const uint8_t EN   = 2;
const uint8_t RW_  = 1;
const uint8_t RS   = 0;

LCD2004::LCD2004(PCF8574AT * i2c)
: HD44780IO()
, _pia(i2c)
, _backLight(0)
{}

LCD2004::~LCD2004()
{}

void LCD2004::setBackLight(uint8_t value)
{
	_backLight = (value ? 1 : 0) << BLUE;
	_pia->set(_backLight);
}

void LCD2004::cmd(uint8_t cmd)
{
	uint8_t msg = _backLight;
	msg |= ((cmd & 0X80) ? 1:0) << DB7;
	msg |= ((cmd & 0X40) ? 1:0) << DB6;
	msg |= ((cmd & 0X20) ? 1:0) << DB5;
	msg |= ((cmd & 0X10) ? 1:0) << DB4;
	enableBit(msg);

	while(isBusy());

	msg = _backLight;
	msg |= ((cmd & 0X08) ? 1:0) << DB7;
	msg |= ((cmd & 0X04) ? 1:0) << DB6;
	msg |= ((cmd & 0X02) ? 1:0) << DB5;
	msg |= ((cmd & 0X01) ? 1:0) << DB4;
	enableBit(msg);

	while(isBusy());
}
     
void LCD2004::data(uint8_t cmd)
{
	uint8_t msg = _backLight;
	msg |= ((cmd & 0X80) ? 1:0) << DB7;
	msg |= ((cmd & 0X40) ? 1:0) << DB6;
	msg |= ((cmd & 0X20) ? 1:0) << DB5;
	msg |= ((cmd & 0X10) ? 1:0) << DB4;
	msg |= 1<<RS;
	enableBit(msg);

	while(isBusy());

	msg = _backLight;
	msg |= ((cmd & 0X08) ? 1:0) << DB7;
	msg |= ((cmd & 0X04) ? 1:0) << DB6;
	msg |= ((cmd & 0X02) ? 1:0) << DB5;
	msg |= ((cmd & 0X01) ? 1:0) << DB4;
	msg |= 1<<RS;
	enableBit(msg);

	while(isBusy());
}

void LCD2004::enableBit(uint8_t msg)
{
	uint8_t octet;

	// ecriture des donnees
	octet = msg & ~(1<<EN);
	_pia->set(octet);
	Tempo::millisecondes(1);

	// debut validation des donnees
	octet = msg | (1<<EN);
	_pia->set(octet);
	Tempo::millisecondes(1);

	// fin validation des donnees
	octet = msg & ~(1<<EN);
	_pia->set(octet);
	Tempo::millisecondes(1);
}

bool LCD2004::isBusy(uint8_t *addressCounter)
{
	uint8_t reg = readCmd();

	if (addressCounter)
	{
		*addressCounter = reg & 0x7F;
	}
	
	return ((reg & 0x80) >> 7);
}

uint8_t LCD2004::readData()
{
	_pia->set(_backLight | (1<<RS) | (1<<RW_));
	Tempo::millisecondes(1);

	uint8_t octet = _pia->get() & 0xF0;
	octet |= (_pia->get() & 0xF0) >> 4;
	return octet;
}

uint8_t LCD2004::readCmd()
{
	_pia->set(_backLight | (1<<RW_));
	Tempo::millisecondes(1);

	uint8_t octet = _pia->get() & 0xF0;
	octet |= (_pia->get() & 0xF0) >> 4;
	return octet;
}

void LCD2004::write(uint8_t value, uint8_t rs, uint8_t rw_)
{
	enableBit(((value & 0xF) << DB4) | (rs << RS) | (rw_ << RW_));
}
