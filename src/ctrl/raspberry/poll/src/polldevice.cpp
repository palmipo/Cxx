#include "polldevice.h"

PollDevice::PollDevice(enum Device::DeviceType type)
: Device(type)
{}

PollDevice::PollDevice(enum Device::DeviceType type, int32_t handler)
: Device(type, handler)
{}
