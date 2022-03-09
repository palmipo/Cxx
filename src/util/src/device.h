#ifndef DEVICE_H
#define DEVICE_H

#include <cstdint>

class Device
{
	public:
		enum DeviceType { GPIO = 1, I2C, SPI, UART, SOCKET, JOYSTICK, CAN } DeviceType;

		Device(enum DeviceType type)
		: _type(type)
		{}

		enum DeviceType type()
		{
		    return _type;
		}

		bool operator==(const Device & device) const
		{
			return (device._type == _type);
		}

	protected:
		enum DeviceType _type;
};

#endif
