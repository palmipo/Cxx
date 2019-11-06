#ifndef BATMINTON_FACTORY_H
#define BATMINTON_FACTORY_H

#include "gpiofactory.h"
#include <termios.h>
#include <string>
#include <chrono>

class HC1632;
class Gpio;
class BatmintonFactory : public GpioFactory
{
	public :
		BatmintonFactory(const std::string &);
		virtual ~BatmintonFactory();

		virtual int32_t status();
		virtual void majAffichage();
		
	protected:
		virtual int32_t actionIn(PollDevice*);
		virtual int32_t actionOut(PollDevice*);
		virtual int32_t actionError(PollDevice*);

		int32_t _status;
		HC1632 * _matrix;
		std::chrono::time_point<std::chrono::high_resolution_clock> _last_valid_irq;
};

#endif /* GPIO_FACTORY_H */
