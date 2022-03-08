#ifndef __MY_PCF8593_H__
#define __MY_PCF8593_H__

#include "devicei2c.h"

class CtrlI2C;
class PCF8593 : public DeviceI2C
{
public:
	PCF8593(uint8_t, CtrlI2C *);

	void getClock(char *hh_mm_ss);
	void setClock(const char *hh_mm_ss);
	void setDate(const char *jj_mm_aa);

	void setAlarm();
	void setAlarmClock(const char *hh_mm_ss);
	void setAlarmDate(const char *jj_mm_aa);
};

#endif
