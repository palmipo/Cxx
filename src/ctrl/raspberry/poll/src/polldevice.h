#ifndef POLL_DEVICE_H
#define POLL_DEVICE_H

#include "device.h"
#include <cstdint>

class PollDevice : public Device
{
	public:
enum { GPIO, UART, SPI, I2C, JOYSTICK } DeviceType;

		PollDevice(DeviceType);
		PollDevice(DeviceType, int32_t);

		virtual int32_t write(uint8_t *, int32_t) = 0;
		virtual int32_t read(uint8_t *, int32_t) = 0;
};

#endif
