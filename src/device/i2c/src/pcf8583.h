#ifndef __PCF8583_H__
#define __PCF8583_H__

#include "devicei2c.h"

class I2C;
class PCF8583 : public DeviceI2C
{
public:
	PCF8583(uint8_t, I2C *);

	void getClock(char *hh_mm_ss);
	void setClock(const char *hh_mm_ss);
	void setDate(const char *jj_mm_aa);

	void setAlarm();
	void setAlarmClock(const char *hh_mm_ss);
	void setAlarmDate(const char *jj_mm_aa);
};

#endif
