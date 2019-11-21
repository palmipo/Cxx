#ifndef __PCF8574AT_H__
#define __PCF8574AT_H__

#include "pcf8574a.h"

class PCF8574AT : public PCF8574A
{
public:
	PCF8574AT(uint8_t, I2C *);
};

#endif
