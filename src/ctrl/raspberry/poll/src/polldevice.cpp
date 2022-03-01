#include "polldevice.h"

PollDevice::PollDevice(Device::Type type)
: Device(type)
{}

PollDevice::PollDevice(Device::Type type, int32_t handler)
: Device(type, handler)
{}
