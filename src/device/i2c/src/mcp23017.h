#ifndef MCP23017_H
#define MCP23017_H

#include "devicei2c.h"

class CtrlI2C;
class MCP23017 : public DeviceI2C
{
public:
	MCP23017(uint8_t, CtrlI2C *);
	virtual ~MCP23017();

	virtual void init(uint8_t port, uint8_t dir=0, uint8_t pol=0, uint8_t pullup=0, uint8_t irq=0, uint8_t defval_pin=0, uint8_t defval=0);
	
	virtual uint8_t getIrq(uint8_t port);

	virtual void set(uint8_t port, uint8_t value);
	virtual uint8_t get(uint8_t port);

private:
	uint8_t _bank;
};

#endif
