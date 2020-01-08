#include "device.h"

Device::Device()
: _handler(-1)
, _max_retry(10)
, _timeout(1000)
{}

Device::Device(int32_t handler)
: _handler(handler)
, _max_retry(10)
, _timeout(1000)
{}

int32_t Device::handler()
{
    return _handler;
}

bool Device::operator==(const Device & device) const
{
	return (device._handler == _handler);
}
