#ifndef GPIO_H
#define GPIO_H

#include "polldevice.h"

class GpioEvent;
class Gpio : public PollDevice
{
	public :
		Gpio(int32_t, int32_t);
		virtual ~Gpio();

		virtual int32_t pinNumber() const;

		virtual int32_t write(uint8_t *, int32_t);
		virtual int32_t read(uint8_t *, int32_t);

		virtual int32_t readEvent();
		
	protected:
		int32_t _pin_number;
};

#endif /* GPIO_H */
