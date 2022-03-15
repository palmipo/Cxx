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

static int32_t callback(PollDevice * device, void *)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "callback");

        // GPIOEVENT_EVENT_RISING_EDGE
        // GPIOEVENT_EVENT_FALLING_EDGE
	uint32_t id;
	uint64_t time;
        int32_t res = ((RaspiGpio *)device)->readEvent(&id, &time);

	std::stringstream ss;
	ss << "callback : device->readEvent() id=" << id << " time=" << time << " " << device->name() << std::endl;
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());

	return res;
}

static void scrute(PollFactory * factory, int32_t * fin)
{
	while (! *fin)
	{
		factory->scrute(100);
	}
}

int main (int argc, char **argv)
{
	int32_t DROITE_PIN = 23;
	int32_t GAUCHE_PIN = 24;
	int32_t FIN_PIN = 9;
	int32_t RAZ_PIN = 10;

	try
	{
		int32_t fin = 0;

		RaspiGpioFactory gpio_factory("/dev/gpiochip0");
		RaspiGpio * gpio_droite = gpio_factory.event(DROITE_PIN);
		RaspiGpio * gpio_gauche = gpio_factory.event(GAUCHE_PIN);
		RaspiGpio * gpio_fin = gpio_factory.event(FIN_PIN);
		RaspiGpio * gpio_raz = gpio_factory.event(RAZ_PIN);

		PollFactory poll_factory;
		poll_factory.setActionInCallback(callback, 0);
		poll_factory.add(gpio_gauche);
		poll_factory.add(gpio_droite);
		poll_factory.add(gpio_fin);
		poll_factory.add(gpio_raz);

		std::thread t(scrute, &poll_factory, &fin);

		Tempo::minutes(10);

		fin = 1;
		Tempo::secondes(200);
		t.join();
	}
	catch(RaspiGpioException & e)
	{
		Log::getLogger()->debug(__FILE__, __LINE__, e.what());
	}

    return 0;
}
