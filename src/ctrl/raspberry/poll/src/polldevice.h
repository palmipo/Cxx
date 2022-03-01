#ifndef POLL_DEVICE_H
#define POLL_DEVICE_H

#include "device.h"
#include <cstdint>

class PollDevice : public Device
{
	public:

		PollDevice(enum Device::DeviceType);
		PollDevice(enum Device::DeviceType, int32_t);

		virtual int32_t write(uint8_t *, int32_t) = 0;
		virtual int32_t read(uint8_t *, int32_t) = 0;
};

#endif
