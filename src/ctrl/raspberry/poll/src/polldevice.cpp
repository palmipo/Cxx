#include "polldevice.h"

PollDevice::PollDevice()
: _handler(-1)
{}

PollDevice::PollDevice(int32_t handler)
: _handler(handler)
{}

int32_t PollDevice::handler()
{
    return _handler;
}

bool PollDevice::operator==(const PollDevice & device) const
{
	return (device._handler == _handler);
}
