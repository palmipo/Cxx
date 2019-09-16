#ifndef GPIO_FACTORY_H
#define GPIO_FACTORY_H

#include "pollfactory.h"
#include <termios.h>
#include <string>

class Gpio;
class GpioFactory : public PollFactory
{
	public :
		GpioFactory(const std::string &);
		virtual ~GpioFactory();

		virtual Gpio * event(int32_t, int32_t);
		virtual Gpio * input(int32_t);
		virtual Gpio * output(int32_t);
	
	protected:
		virtual int32_t actionIn(PollDevice*);
		virtual int32_t actionOut(PollDevice*);
		virtual int32_t actionError(PollDevice*);

	protected:
		int32_t _handler;
		std::map < int32_t, Gpio * > _map;
};

#endif /* GPIO_FACTORY_H */
