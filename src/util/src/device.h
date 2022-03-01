#ifndef DEVICE_H
#define DEVICE_H

#include <cstdint>

class Device
{
	public:
		Device(DeviceType);
		Device(DeviceType, int32_t);

enum { GPIO, I2C, SPI, UART, JOYSTICK } DeviceType;
		virtual int32_t handler();

		bool operator==(const Device &) const;

	protected:
		int32_t _handler;

	protected:
		int32_t _max_retry;
		int32_t _timeout;
};

#endif
