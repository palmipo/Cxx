#ifndef DEVICEPWM_H
#define DEVICEPWM_H

#include "device.h"
#include <cstdint>

class DevicePwm : public Device
{
DevicePwm()
: Device(Device::DeviceType_PWM_DEVICE)
{}

};

#endif /* DEVICEPWM /*
