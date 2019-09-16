#include "lcd2004.h"
#include "pia.h"
#include "hd44780.h"
#include "pcf8574at.h"
#include <poll.h>
#include <iostream>

const u8 DB7  = 7;
const u8 DB6  = 6;
const u8 DB5  = 5;
const u8 DB4  = 4;
const u8 BLUE = 3;
const u8 EN   = 2;
const u8 RW_  = 1;
const u8 RS   = 0;

lcd2004::lcd2004(I2C *i2c)
: HD44780IO()
, _pia(0)
, _backLight(0)
, _afficheur(0)
{
	_pia = new PCF8574AT(0, i2c);

	_afficheur = new HD44780(this);
}

lcd2004::~lcd2004()
{
	delete _afficheur;
	delete _pia;
}

HD44780 * lcd2004::lcd()
{
	return _afficheur;
}

void lcd2004::setBackLight(u8 value)
{
	_backLight = (value ? 1 : 0) << BLUE;
	_pia->set(0, _backLight);
}

void lcd2004::cmd(u8 cmd)
{
	u8 msg = _backLight;
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
     
void lcd2004::data(u8 cmd)
{
	u8 msg = _backLight;
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

void lcd2004::enableBit(u8 msg)
{
	u8 octet;

	// ecriture des donnees
	octet = msg & ~(1<<EN);
	_pia->set(0, octet);
	poll(0, 0, 1);

	// debut validation des donnees
	octet = msg | (1<<EN);
	_pia->set(0, octet);
	poll(0, 0, 1);

	// fin validation des donnees
	octet = msg & ~(1<<EN);
	_pia->set(0, octet);
	poll(0, 0, 1);
}

bool lcd2004::isBusy(u8 *addressCounter)
{
	u8 reg = readCmd();

	if (addressCounter)
	{
		*addressCounter = reg & 0x7F;
	}
	
	return ((reg & 0x80) >> 7);
}

u8 lcd2004::readData()
{
	_pia->set(0, _backLight | (1<<RS) | (1<<RW_));
	poll(0, 0, 1);

	u8 octet = _pia->get(0) & 0xF0;
	octet |= (_pia->get(0) & 0xF0) >> 4;
	return octet;
}

u8 lcd2004::readCmd()
{
	_pia->set(0, _backLight | (1<<RW_));
	poll(0, 0, 1);

	u8 octet = _pia->get(0) & 0xF0;
	octet |= (_pia->get(0) & 0xF0) >> 4;
	return octet;
}

void lcd2004::write(u8 value, u8 rs, u8 rw_)
{
	enableBit(((value & 0xF) << DB4) | (rs << RS) | (rw_ << RW_));
}
