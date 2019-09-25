#ifndef BATMINTON_FACTORY_H
#define BATMINTON_FACTORY_H

#include "gpiofactory.h"
#include <termios.h>
#include <string>

class HC1632;
class Gpio;
class BatmintonFactory : public GpioFactory
{
	public :
		BatmintonFactory(const std::string &);
		virtual ~BatmintonFactory();
		virtual int32_t majAffichage();
		
	protected:
		virtual int32_t actionIn(PollDevice*);
		virtual int32_t actionOut(PollDevice*);
		virtual int32_t actionError(PollDevice*);

		HC1632 * _matrix;
};

#endif /* GPIO_FACTORY_H */
