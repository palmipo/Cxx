#include "gpiofactory.h"
#include "gpio.h"
#include "gpioexception.h"
#include "log.h"

#include <linux/gpio.h>
#include <sstream>
#include <thread>
#include <cstdlib>

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
		uint8_t PIN[] = { 18, 17, 27, 23, 22, 24, 10, 25, 9, 8, 11, 7, 5, 12, 6, 13 };
		Test factory;

		uint8_t valeur = 0;
		for (int32_t i=0; i<16; ++i)
		{
			factory.output(PIN[i])->write(&valeur, 1);
		}

//		factory.event(4, GPIOEVENT_REQUEST_BOTH_EDGES);

		while(1)
		{
//			int32_t etat = factory.scrute(1000);

			valeur = random() % 7;
			uint8_t val1 = valeur & 1;
			uint8_t val2 = valeur & 2;
			uint8_t val3 = valeur & 4;
			factory.output(PIN[0])->write(&val1, 1);
			factory.output(PIN[3])->write(&val1, 1);

			factory.output(PIN[1])->write(&val2, 1);
			factory.output(PIN[4])->write(&val2, 1);

			factory.output(PIN[2])->write(&val3, 1);
			factory.output(PIN[5])->write(&val3, 1);
			std::this_thread::sleep_for(std::chrono::milliseconds(250));


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
