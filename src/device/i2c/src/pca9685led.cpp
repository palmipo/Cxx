#include "pca9685led.h"

PCA9685Led::PCA9685Led()
: _offset_on(0)
, _offset_off(0)
{}

PCA9685Led::~PCA9685Led()
{}

uint16_t PCA9685Led::getOffsetON()
{
	return _offset_on;
}

void PCA9685Led::setOffsetON(uint16_t value)
{
	_offset_on = value & 0x0FFF;
}

uint16_t PCA9685Led::getOffsetOFF()
{
	return _offset_off;
}

void PCA9685Led::setOffsetOFF(uint16_t value)
{
	_offset_off = value & 0x1FFF;
}
