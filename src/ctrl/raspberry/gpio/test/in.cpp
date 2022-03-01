#include "raspigpio.h"
#include "raspigpiofactory.h"
#include "raspigpioexception.h"
#include "log.h"
#include "tempo.h"
#include "polldevice.h"
#include "pollfactory.h"
#include <cstdint>
#include <sstream>
#include <thread>

int32_t callback(PollDevice * device, void *)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "callback");

        // GPIOEVENT_EVENT_RISING_EDGE
        // GPIOEVENT_EVENT_FALLING_EDGE
	uint32_t id;
	uint64_t time;
        int32_t res = ((RaspiGpio *)device)->readEvent(&id, &time);

	std::stringstream ss;
	ss << "callback : device->readEvent() id=" << id << " time=" << time << std::endl;
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());

	return res;
}

void scrute(PollFactory * factory, int32_t * fin)
{
	while (! *fin)
	{
		factory->scrute(1000);
	}
}

int main (int argc, char **argv)
{
	try
	{
		int32_t fin = 0;

		RaspiGpioFactory gpio_factory("/dev/gpiochip0");
		RaspiGpio * gpio = gpio_factory.event(17);

		PollFactory poll_factory;
		poll_factory.setActionInCallback(callback, 0);
		poll_factory.add(gpio);

		std::thread t(scrute, &poll_factory, &fin);

		Tempo::minutes(10);

		fin = 1;
		t.join();
	}
	catch(RaspiGpioException & e)
	{
		Log::getLogger()->debug(__FILE__, __LINE__, e.what());
	}

    return 0;
}
