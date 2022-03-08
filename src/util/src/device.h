#ifndef DEVICE_H
#define DEVICE_H

#include <cstdint>

class Device
{
	public:
		enum DeviceType { GPIO = 1, I2C, SPI, UART, SOCKET, JOYSTICK, CAN } DeviceType;

		Device(enum DeviceType);

		enum DeviceType type();

		bool operator==(const Device &) const;

	protected:
		enum DeviceType _type;
};

#endif
