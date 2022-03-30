#include "raspiuart.h"
#include "rs232.h"

RaspiUart::RaspiUart(RS232 * serial)
: CtrlUART()
, _serial(serial)
{}

RaspiUart::~RaspiUart()
{}

int32_t RaspiUart::read(uint8_t * data, int32_t length)
{
	return _serial->read(data, length);
}

int32_t RaspiUart::write(uint8_t * data, int32_t length)
{
	return _serial->write(data, length);
}

