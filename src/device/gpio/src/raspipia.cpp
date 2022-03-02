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
	_gpio->write(&val, 1);
}

uint8_t RaspiPia::read()
{
	uint8_t val;
	_gpio->read(&val, 1);
	return val;
}

