#include "ada1334.h"
#include "raspii2c.h"
#include "i2cexception.h"
#include "pollfactory.h"
#include "polldevice.h"
#include "raspipia.h"
#include "raspigpiofactory.h"
#include "raspigpioexception.h"
#include "tempo.h"
#include "log.h"
#include <sstream>
#include <thread>
#include <iomanip>

static int32_t action(PollDevice * device, void * user_data)
{
	uint32_t id = 0;
	uint64_t timestamp = 0;
	((RaspiGpio *)device)->readEvent(&id, &timestamp);

	ADA1334 * capteur = (ADA1334 *)user_data;
}

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
		int32_t pin_out = 18;
		int32_t pin_in = 4;

		RaspiI2C i2c_bus("/dev/i2c-1");

		RaspiGpioFactory fact("/dev/gpiochip0");
		RaspiGpio * gpio_led = fact.outputs(&pin, 1);
		RaspiGpio * gpio_irq = fact.event(pin_in);

		RaspiPia led(gpio_led);

		ADA1334 capteur(&led, &i2c_bus);

		PollFactory poll_fact;
		poll_fact.setActionInCallback(action, &capteur);
		poll_fact.add(gpio_irq);

		int32_t fin = 0;
		std::thread my_thread(scrute, &poll_fact, &fin);
		Tempo::minutes(10);

		fin = 1;
		Tempo::minutes(1);
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

