#include "polldevice.h"

PollDevice::PollDevice(uint8_t type)
: Device(type)
, _handler(-1)
{}

PollDevice::PollDevice(uint8_t type, int32_t handler)
: Device(type)
, _handler(handler)
{}

int32_t PollDevice::handler()
{
    return _handler;
}

bool PollDevice::operator==(const PollDevice & device) const
{
	return (device._handler == _handler);
}
