#ifndef __I2C_DEVICE_H__
#define __I2C_DEVICE_H__

#include <cstdint>

class I2C;
class DeviceI2C
{
	public:
		DeviceI2C(uint8_t addr, I2C * bus)
		: _address(addr)
		, _twi(bus)
		{}

	protected:
		I2C * _twi;
		uint8_t _address;
};

#endif /* __I2C_DEVICE_H__ */
