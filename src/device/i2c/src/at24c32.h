#ifndef __AT24C32_H__
#define __AT24C32_H__

#include "devicei2c.h"

// class I2C;
class AT24C32 : public DeviceI2C
{
public:
	AT24C32(I2C *);

	virtual void write(uint16_t addr, uint8_t value);
	virtual uint8_t read(uint16_t addr);
};

#endif
