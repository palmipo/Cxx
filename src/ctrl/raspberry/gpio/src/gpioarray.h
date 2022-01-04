#ifndef GPIOARRAY_H
#define GPIOARRAY_H

#include "polldevice.h"
#include <linux/gpio.h>

class GpioArray : public PollDevice
{
	public :
		GpioArray(int32_t);
		virtual ~GpioArray();

		virtual void set(int32_t, uint8_t);
		virtual uint8_t get(int32_t);

		virtual void write();
		virtual void read();
		
	protected:
		struct gpiohandle_data _values;
};

#endif /* GPIO_H */
