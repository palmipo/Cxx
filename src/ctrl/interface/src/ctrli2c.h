#ifndef CTRLI2C_H
#define CTRLI2C_H

#include "device.h"
#include <cstdint>

class CtrlI2C : public Device
{
public:
	CtrlI2C()
	: Device(Device::DeviceType_I2C)
	{}

	virtual ~CtrlI2C()
	{}

	virtual void set (uint8_t addr, uint8_t* buf, int32_t len) = 0;
	virtual void get (uint8_t addr, uint8_t* buf, int32_t len) = 0;
	virtual void transfer (uint8_t addr, uint8_t* cmd, int32_t cmd_len, uint8_t* buf, int32_t buf_len) = 0;
};

#endif /* CTRLI2C_H */
