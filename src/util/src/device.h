#ifndef DEVICE_H
#define DEVICE_H

#include <cstdint>

class Device
{
	public:
		enum DeviceType { GPIO = 1, I2C, SPI, UART, SOCKET, JOYSTICK, CAN } DeviceType;

		Device(enum DeviceType);

		virtual int32_t handler();
		virtual enum DeviceType type();

		bool operator==(const Device &) const;

	protected:
		int32_t _max_retry;
		int32_t _timeout;
		enum DeviceType _type;
};

#endif
