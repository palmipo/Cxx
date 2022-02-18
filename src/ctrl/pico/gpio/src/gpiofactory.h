#ifndef GPIO_FACTORY_H
#define GPIO_FACTORY_H

#include "pollfactory.h"
#include <linux/gpio.h>
#include <string>

class Gpio;
class GpioArray;
class GpioFactory : public PollFactory
{
	public :
		/*
		 * device : /dev/gpiochip0
		 */
		GpioFactory(const std::string &);
		virtual ~GpioFactory();

		// GPIOHANDLE_REQUEST_INPUT
		// GPIOHANDLE_REQUEST_OUTPUT
		// GPIOHANDLE_REQUEST_ACTIVE_LOW
		// GPIOHANDLE_REQUEST_OPEN_DRAIN
		// GPIOHANDLE_REQUEST_OPEN_SOURCE

		// GPIOEVENT_REQUEST_RISING_EDGE
		// GPIOEVENT_REQUEST_FALLING_EDGE
		// GPIOEVENT_REQUEST_BOTH_EDGES;
		virtual Gpio * event(int32_t, int32_t = GPIOEVENT_REQUEST_BOTH_EDGES, int32_t = GPIOHANDLE_REQUEST_INPUT);

		virtual Gpio * input(int32_t);
		//~ virtual Gpio *  inputs(int32_t*, int32_t);

		virtual Gpio * output(int32_t);
		//~ virtual Gpio *  outpquts(int32_t*, int32_t);

		virtual void info();
	
	protected:
		int32_t _handler;
		std::map < int32_t, int32_t > _event_map;
		std::map < int32_t, Gpio * > _io_map;
};

#endif /* GPIO_FACTORY_H */
