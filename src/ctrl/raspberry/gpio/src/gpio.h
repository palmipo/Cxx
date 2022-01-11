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

		virtual void write(uint8_t);
		virtual int32_t read();

		// GPIOEVENT_EVENT_RISING_EDGE
		// GPIOEVENT_EVENT_FALLING_EDGE
		virtual int32_t readEvent(uint32_t * = 0, uint64_t * = 0);
		
	protected:
		int32_t _pin_number;
};

#endif /* GPIO_H */
