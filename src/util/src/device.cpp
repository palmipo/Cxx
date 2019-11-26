#include "device.h"

Device::Device()
: _handler(-1)
{}

Device::Device(int32_t handler)
: _handler(handler)
{}

int32_t Device::handler()
{
    return _handler;
}

bool Device::operator==(const Device & device) const
{
	return (device._handler == _handler);
}
