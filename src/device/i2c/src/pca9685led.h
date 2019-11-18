#ifndef PCA9685_LED_H
#define PCA9685_LED_H

#include <cstdint>

class PCA9685Led
{
public:
	PCA9685Led();
	virtual ~PCA9685Led();

	virtual uint16_t getOffsetON();
	virtual void setOffsetON(uint16_t);

	virtual uint16_t getOffsetOFF();
	virtual void setOffsetOFF(uint16_t);

private:
	uint16_t _offset_on;
	uint16_t _offset_off;
};

#endif
