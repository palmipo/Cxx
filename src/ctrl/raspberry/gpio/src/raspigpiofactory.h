#ifndef RASPIGPIO_FACTORY_H
#define RASPIGPIO_FACTORY_H

#include <linux/gpio.h>
#include <string>
#include <map>

class RaspiGpio;
class RaspiGpioFactory
{
	public :
		/*
		 * device : /dev/gpiochip0
		 */
		RaspiGpioFactory(const std::string &);
		virtual ~RaspiGpioFactory();

		// GPIOHANDLE_REQUEST_INPUT
		// GPIOHANDLE_REQUEST_OUTPUT
		// GPIOHANDLE_REQUEST_ACTIVE_LOW
		// GPIOHANDLE_REQUEST_OPEN_DRAIN
		// GPIOHANDLE_REQUEST_OPEN_SOURCE

		// GPIOEVENT_REQUEST_RISING_EDGE
		// GPIOEVENT_REQUEST_FALLING_EDGE
		// GPIOEVENT_REQUEST_BOTH_EDGES;
		virtual RaspiGpio * event(int32_t, int32_t = GPIOEVENT_REQUEST_BOTH_EDGES, int32_t = GPIOHANDLE_REQUEST_INPUT);

		virtual RaspiGpio * inputs(int32_t *, int32_t);

		virtual RaspiGpio * outputs(int32_t *, int32_t);

		virtual void info();
	
	protected:
		int32_t _handler;
		std::map < int32_t, RaspiGpio * > _io_map;
};

#endif /* RASPIGPIO_FACTORY_H */
