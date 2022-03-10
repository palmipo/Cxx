#ifndef DEVICESPI_H
#define DEVICESPI_H

#include "device.h"

class DeviceSPI : public Device
{
DeviceSPI()
: Device(DeviceType_SPI_DEVICE)
{}

virtual ~DeviceSPI()
{}

};

#endif /* DEVICESPI_H */
