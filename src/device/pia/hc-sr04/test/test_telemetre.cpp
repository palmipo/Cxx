#include "hc_sr04.h"
#include "log.h"
#include "tempo.h"
#include "raspigpiofactory.h"
#include "raspigpio.h"
#include "raspipia.h"
#include "pollfactory.h"
#include "polldevice.h"
#include <sstream>
#include <thread>
#include <chrono>

int32_t callback(PollDevice * device, void * user_data)
{
	uint32_t evnt;
	uint64_t time;

	((RaspiGpio *)device)->readEvent(&evnt, &time);
	HC_SR04 * telemetre = (HC_SR04 *)user_data;

	if (evnt == GPIOEVENT_EVENT_RISING_EDGE)
	{
		telemetre->setTimeRising(time);
	}
	else if (evnt == GPIOEVENT_EVENT_FALLING_EDGE)
	{
		telemetre->setTimeFalling(time);
	}
	
	return 0;
}

void scrute(PollFactory * fact, int32_t * fin)
{
	while (!*fin)
	{
		fact->scrute(100);
	}
}

int main(int argc,char **argv)
{
	RaspiGpioFactory gpio_fact("/dev/gpiochip0");
	int32_t pin_out = 17;
	int32_t pin_in = 18;
	RaspiGpio * out = gpio_fact.outputs(&pin_out, 1);
	RaspiGpio * in = gpio_fact.event(pin_in);

	RaspiPia pia(out);

	HC_SR04 telemetre(&pia);

	PollFactory poll_fact;
	poll_fact.setActionInCallback(callback, &telemetre);
	poll_fact.add(in);
	poll_fact.add(out);

	int32_t fin = 0;
	std::thread t(scrute, &poll_fact, &fin);

	telemetre.start();

	while (telemetre.isBusy());
	fin = 1;

	uint64_t dst = telemetre.distance();

	std::stringstream ss;
	ss << "distance : " << dst << " mm.";
	Log::getLogger()->info(__FILE__, __LINE__, ss.str());

	return 0;
}
