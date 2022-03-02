#include "hc_sr04.h"
#include "log.h"
#include <sstream>
#include <thread>
#include <chrono>

void callback(PollDevice * device, void * user_data)
{
	int32_t id;
	uint64_t time;
	(RaspiGpio *)device)->readEvent(&id, &time);

	Telemetre * tele = (Telemetre *)user_data;
	tele->event(id, time);
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
	RaspiGpioFactory gpio_fact("/dev/");
	int32_t pin_out = 17;
	int32_t pin_in = 18;
	RaspiGpio * out = gpio_fact.outputs(&pin_out, 1);
	RaspiGpio * in = gpio_fact.event(pin_in);

	HC_SR04 telemetre(out);

	PollFactory poll_fact;
	poll_fact.setActionInCallback(callback, &telemetre);
	poll_fact.add(in);

	int32_t fin = 0;
	std::thread t(scrute, &poll_fact, &fin);

	telemetre.start();

	Tempo::minutes(1);

	while (!telemetre.status());
	fin = 1;

	uint64_t dst = telemetre.distance();

	std::stringstream ss;
	ss << "distance : " << dst << " mm.";
	Log::getLogger()->info(__FILE__, __LINE__, ss.str());

	return 0;
}
