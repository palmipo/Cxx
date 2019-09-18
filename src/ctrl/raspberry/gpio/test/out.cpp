#include "gpiofactory.h"
#include "gpio.h"
#include "gpioexception.h"
#include "log.h"

#include <linux/gpio.h>
#include <sstream>

class Test : public GpioFactory
{
	public:
		Test()
		: GpioFactory("/dev/gpiochip0")
		{}

	protected:
		virtual int32_t actionIn(PollDevice * device)
		{
			int32_t etat = device->actionIn();
			if (etat & GPIOEVENT_EVENT_RISING_EDGE)
				Log::getLogger()->info(__FILE__, __LINE__, "RISING");

			if (etat & GPIOEVENT_EVENT_FALLING_EDGE)
				Log::getLogger()->info(__FILE__, __LINE__, "FALLING");
			return 0;
		}

		virtual int32_t actionOut(PollDevice*)
		{
			return 0;
		}

		virtual int32_t actionError(PollDevice*)
		{
			return 0;
		}
};

int main(int argc, char **argv)
{
	try
	{
		Test factory;

		uint8_t valeur = 0;
		factory.output(18)->write(&valeur, 1);
		

		factory.event(4, GPIOEVENT_REQUEST_BOTH_EDGES, GPIOHANDLE_REQUEST_ACTIVE_LOW);

		while(1)
		{
			int32_t etat = factory.scrute(1000);

		}
	}
	catch(GpioException e)
	{
		Log::getLogger()->error(__FILE__, __LINE__, e.what());
	}
	catch(...)
	{
		Log::getLogger()->error(__FILE__, __LINE__, "exception");
	}

	return 0;
}
