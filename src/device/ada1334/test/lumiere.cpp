#include "ada1334.h"
#include "raspii2c.h"
#include "i2cexception.h"
#include "gpiofactory.h"
#include "gpioexception.h"
#include "log.h"
#include <sstream>
#include <thread>
#include <iomanip>

static void scrute(PollFactory * factory, bool fin)
{
	while (!fin)
	{
		factory->scrute();
	}
}

int main(int argc, char **argv)
{
	try
	{
		RaspiI2C i2c_bus("/dev/i2c-1");

		GpioFactory fact("/dev/gpiochip0");
		Gpio * gpio_led = fact.output(18);
		Gpio * gpio_irq = fact.event();

		RaspiGpio led(gpio_led);
		RaspiGpio irq(gpio_irq);

		ADA1334 capteur(&led, &irq, &i2c_bus);
		capteur.led(0);

		int32_t cpt=0;
		while(cpt < 60)
		{
			fact.scrute(1000);
			++cpt;
		}
	}
	catch(I2CException e)
	{
		Log::getLogger()->error(__FILE__, __LINE__, e.what());
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

