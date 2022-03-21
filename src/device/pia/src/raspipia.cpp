#include "raspipia.h"
#include "raspigpio.h"

RaspiPia::RaspiPia(RaspiGpio * gpio)
: PIA()
, _gpio(gpio)
{}

RaspiPia::~RaspiPia()
{}

void RaspiPia::write(uint8_t val)
{
	uint8_t data[_gpio->pinNumber()];
	for (int32_t i=0; i<_gpio->pinNumber(); ++i)
	{
		data[i] = (val & (1<<i)) ? 1 : 0;
	}
	_gpio->write(data, _gpio->pinNumber());
}

uint8_t RaspiPia::read()
{
	uint8_t data[_gpio->pinNumber()];
	_gpio->read(data, _gpio->pinNumber());
	uint8_t val = 0;
	for (int32_t i=0; i<_gpio->pinNumber(); ++i)
	{
		val |= data[i] << i;
	}
	return val;
}

