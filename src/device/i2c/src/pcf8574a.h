#ifndef __PCF8574A_H__
#define __PCF8574A_H__

#include "devicei2c.h"

class I2C;
class PCF8574A : public DeviceI2C
{
public:
	PCF8574A(uint8_t, I2C *);
	
	virtual void setDirection(uint8_t port, uint8_t direction);
	virtual uint8_t getDirection(uint8_t port);
	
	virtual void set(uint8_t port, uint8_t value);
	virtual uint8_t get(uint8_t port);

protected:
	uint8_t _direction;
};

#endif
