#ifndef DEVICE_H
#define DEVICE_H

#include <cstdint>
#include <string>

class Device
{
	public:
		const uint8_t DeviceType_GPIO = 1;
		const uint8_t DeviceType_I2C = 2;
		const uint8_t DeviceType_SPI = 3;
		const uint8_t DeviceType_UART = 4;
		const uint8_t DeviceType_SOCKET = 5;
		const uint8_t DeviceType_JOYSTICK = 6;
		const uint8_t DeviceType_CAN = 7;
		const uint8_t DeviceType_I2C_DEVICE = 8;
		const uint8_t DeviceType_SPI_DEVICE = 9;
		const uint8_t DeviceType_UART_DEVICE = 10;
		const uint8_t DeviceType_PWM_DEVICE = 11;

		Device(uint8_t type)
		: _type(type)
		{}

		uint8_t type()
		{
		    return _type;
		}

		bool operator==(const Device & device) const
		{
			return (device._type == _type);
		}

		virtual void setName(const std::string & name)
		{
			_nom = name;
		}

		virtual std::string name() const
		{
			return _nom;
		}

	protected:
		uint8_t _type;
		std::string _nom;
};

#endif
