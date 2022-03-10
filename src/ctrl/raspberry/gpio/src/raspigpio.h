#ifndef RASPIGPIO_H
#define RASPIGPIO_H

#include "polldevice.h"
#include <linux/gpio.h>

class RaspiGpio : public PollDevice
{
	public :
		RaspiGpio(int32_t *, int32_t, int32_t);
		virtual ~RaspiGpio();

		virtual int32_t pinNumber(int32_t) const;

		virtual int32_t write(uint8_t *, int32_t);
		virtual int32_t read(uint8_t *, int32_t);

		// GPIOEVENT_EVENT_RISING_EDGE
		// GPIOEVENT_EVENT_FALLING_EDGE
		virtual int32_t readEvent(uint32_t * = 0, uint64_t * = 0);

	protected:
		int32_t * _pins_number;
		int32_t _pins_length;
};

#endif /* RASPIGPIO_H */
