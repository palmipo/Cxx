#include "polldevice.h"

PollDevice::PollDevice(PollDevice::DeviceType type)
: Device(type)
{}

PollDevice::PollDevice(PollDevice::DeviceType type, int32_t handler)
: Device(type, handler)
{}
