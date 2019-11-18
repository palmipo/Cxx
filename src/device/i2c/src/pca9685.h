#ifndef PCA9685_H
#define PCA9685_H

#include "devicei2c.h"

class I2C;
class PCA9685Led;
class PCA9685 : public DeviceI2C
{
public:
	PCA9685(uint8_t addr, I2C * ctrl);
	virtual ~PCA9685();

	virtual void restart();
	virtual void reset();

	virtual PCA9685Led *getLed(uint8_t num);

	virtual void read(uint8_t port);
	virtual void write(uint8_t port);
	virtual void writeAll();

	virtual uint8_t getAutoIncrement();
	virtual void setAutoIncrement(uint8_t on_off);

	virtual uint8_t getOutputChangeOnAck();
	virtual void setOutputChangeOnAck(uint8_t on_off);

	virtual uint8_t getOutDrv();
	virtual void setOutDrv(uint8_t on_off);

	virtual uint8_t getInvertOutput();
	virtual void setInvertOutput(uint8_t on_off);

	virtual void setAllLeds(uint16_t value_on, uint16_t value_off);
	virtual void setAllLedsOn();
	virtual void setAllLedsOff();

	virtual void setExternalClock(uint8_t on_off, uint32_t frequency);

	virtual uint8_t getPrescaler();
	virtual void setPwmFrequency(uint32_t frequency);
	virtual void setPrescaler(uint8_t prescale_value);

	virtual void setSubAddress1(uint8_t on_off, uint8_t value);
	virtual void setSubAddress2(uint8_t on_off, uint8_t value);
	virtual void setSubAddress3(uint8_t on_off, uint8_t value);

	virtual void setAllCallAddress(uint8_t on_off, uint8_t value);

protected:
	virtual void getModes();
	virtual void setModes();

protected:
	uint8_t _mode1, _mode2;
	uint32_t _clock;
	PCA9685Led *_leds;
};

#endif
