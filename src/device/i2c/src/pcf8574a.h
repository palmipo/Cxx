#ifndef __PCF8574A_H__
#define __PCF8574A_H__

#include "devicei2c.h"

class CtrlI2C;
class PCF8574A : public DeviceI2C
{
public:
	PCF8574A(uint8_t, CtrlI2C *);
	
	virtual void setDirection(uint8_t direction);
	virtual uint8_t getDirection();
	
	virtual void set(uint8_t value);
	virtual uint8_t get();

protected:
	uint8_t _direction;
};

#endif
