#include "device.h"

Device::Device(enum Device::DeviceType type)
: _type(type)
{}

bool Device::operator==(const Device & device) const
{
	return (device._type == _type);
}

enum Device::DeviceType Device::type()
{
    return _type;
}
