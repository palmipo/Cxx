#ifndef __AT24C32_H__
#define __AT24C32_H__

#include "devicei2c.h"

class CtrlI2C;
class AT24C32 : public DeviceI2C
{
public:
	AT24C32(CtrlI2C *);

	virtual void write(uint16_t, uint8_t *, int32_t);
	virtual void read(uint16_t, uint8_t *, int32_t);
};

#endif
