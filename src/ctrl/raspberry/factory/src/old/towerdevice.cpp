#include "towerdevice.h"
#include "polldevice.h"

TowerDevice::TowerDevice(PollDevice * dev)
: _device(dev)
{}

int32_t TowerDevice::handler()
{
	return _device->handler();
}
