#ifndef __I2C_DEVICE_H__
#define __I2C_DEVICE_H__

#include "device.h"
#include <cstdint>

class CtrlI2C;
class DeviceI2C : public Device
{
	public:
		DeviceI2C(uint8_t addr, CtrlI2C * bus)
		: Device(DeviceType::I2C)
		, _address(addr)
		, _twi(bus)
		{}

	protected:
		CtrlI2C * _twi;
		uint8_t _address;
};

#endif /* __I2C_DEVICE_H__ */
