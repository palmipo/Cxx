#ifndef __DS1307_H__
#define __DS1307_H__

#include "devicei2c.h"

class I2C;
class DS1307 : public DeviceI2C
{
public:
	DS1307(I2C *);

	void setDate(const char * date);
	void setTime(const char * time);
	void date(char * date);
	void time(char * time);
	void setSquareWave(uint8_t frequence);
	void setMemory(uint8_t addr, uint8_t * mem, uint32_t length);
	void memory(uint8_t addr, uint8_t * buffer, uint32_t length);
	uint8_t haltClock(uint8_t halt);
	uint8_t clockHalted();
};

#endif
