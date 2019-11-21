#include "pcf8574a.h"
#include "i2c.h"

PCF8574A::PCF8574A(uint8_t address, I2C * i2c)
: DeviceI2C(0x38 | (address & 0x7), i2c)
, _direction(0)
{}

void PCF8574A::setDirection(uint8_t port, uint8_t direction)
{
	_direction = direction;
	_twi->set(_address, &_direction, 1);
}

uint8_t PCF8574A::getDirection(uint8_t port)
{
	return _direction;
}

void PCF8574A::set (uint8_t port, uint8_t valeur)
{
	uint8_t byte = valeur | _direction;
	_twi->set(_address, &byte, 1);
}

uint8_t PCF8574A::get (uint8_t port)
{
	uint8_t valeur = 0;
	_twi->get(_address, &valeur, 1);
	
	return valeur & _direction;
}
