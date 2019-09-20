#include "hc_sr04.h"
#include "gpio.h"
#include "gpioevent.h"
#include "log.h"
#include <thread>
#include <sstream>

HC_SR04::HC_SR04(int32_t OUT_PIN, int32_t IRQ_PIN)
: GpioFactory("/dev/gpiochip0")
, timestamp_rising(0)
, timestamp_falling(0)
{
	out = output(OUT_PIN);
	in = event(IRQ_PIN, GPIOEVENT_REQUEST_BOTH_EDGES, GPIOHANDLE_REQUEST_OPEN_DRAIN);
}

int64_t HC_SR04::distance()
{
	uint8_t valeur;

	valeur = 1;
	out->write(&valeur, 1);

	std::this_thread::sleep_for(std::chrono::microseconds(10));

	valeur = 0;
	out->write(&valeur, 1);

	scrute(1000);
	scrute(1000);

	// vitesse du son : 340m/s
	int64_t distance = abs(timestamp_falling - timestamp_rising);
	std::stringstream ss;
	ss << "distance : " << distance;
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());

	return distance * 17 / 100000;
}

int32_t HC_SR04::actionIn(PollDevice * device)
{
	// Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	Gpio * io = (Gpio *)device;
	int32_t etat = io->actionIn();
	if (etat)
	{
		// Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");
		GpioEvent * evnt = io->getEvent();
		if (evnt->id() == GPIOEVENT_EVENT_RISING_EDGE)
		{
			timestamp_rising = evnt->timestamp();
			// std::stringstream ss;
			// ss << "GPIOEVENT_EVENT_RISING_EDGE : " << timestamp_rising;
			// Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		}
		else if (evnt->id() == GPIOEVENT_EVENT_FALLING_EDGE)
		{
			timestamp_falling = evnt->timestamp();
			// std::stringstream ss;
			// ss << "GPIOEVENT_EVENT_FALLING_EDGE : " << timestamp_falling;
			// Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		}
	}
	
	return etat;
}

int32_t HC_SR04::actionOut(PollDevice * device)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionOut");

	return device->actionOut();
}

int32_t HC_SR04::actionError(PollDevice * device)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionError");

	return device->actionError();
}
