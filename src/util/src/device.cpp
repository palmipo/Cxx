#include "device.h"

Device::Device(Device::Type type)
: _handler(-1)
, _max_retry(10)
, _timeout(1000)
, _type(type)
{}

Device::Device(Device::Type type, int32_t handler)
: _handler(handler)
, _max_retry(10)
, _timeout(1000)
, _type(type)
{}

int32_t Device::handler()
{
    return _handler;
}

bool Device::operator==(const Device & device) const
{
	return (device._handler == _handler);
}

Device::Type Device::type()
{
    return _type;
}
