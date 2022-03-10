#ifndef CTRLSPI_H
#define CTRLSPI_H

#include "device.h"
#include <cstdint>

class CtrlSPI : public Device
{
public:
	CtrlSPI()
	:Device(Device::DeviceType_SPI)
	{}

	virtual ~CtrlSPI()
	{}

	virtual void set (uint8_t* buf, int32_t len) = 0;
	virtual void get (uint8_t* buf, int32_t len) = 0;
	virtual void transfer (uint8_t* cmd, uint8_t* buf, int32_t len) = 0;
};

#endif /* CTRLSPI_H */
