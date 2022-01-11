#include "hc_sr04.h"
#include "gpio.h"
#include "gpiofactory.h"
#include "log.h"
#include <sstream>
#include <chrono>

HC_SR04::HC_SR04(int32_t OUT_PIN, int32_t IRQ_PIN)
: GpioFactory("/dev/gpiochip0")
, _distance(0.)
, _thread(0)
, _fin(1)
{
	_out = output(OUT_PIN);
	_in = event(IRQ_PIN, GPIOEVENT_REQUEST_BOTH_EDGES);
}

HC_SR04::~HC_SR04()
{
	_fin = 1;
	delete _thread;
}

void HC_SR04::stop()
{
	_fin = 1;
}

void HC_SR04::start(int32_t intervalle_500ms)
{
	_fin = 0;
	_intervalle_500ms = (intervalle_500ms > 0) ? intervalle_500ms : 1;
	_thread = new std::thread(run, this);
	_thread->detach();

	_out->write(1);

	std::this_thread::sleep_for(std::chrono::microseconds(10));

	_out->write(0);

	//~ std::this_thread::sleep_for(std::chrono::milliseconds(500 * obj->_intervalle_500ms));
}

void HC_SR04::run(HC_SR04 * obj)
{
	while (!obj->_fin)
	{
		obj->scrute(1000);
	}
}

int32_t HC_SR04::status()
{
	return _status;
}

double HC_SR04::distance()
{
	_status = 0;
	return _distance;
}

int32_t HC_SR04::actionIn(PollDevice * device)
{
	// Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	Gpio * io = (Gpio *)device;
	if (io)
	{
		int32_t evnt = io->readEvent();
		if (evnt == GPIOEVENT_EVENT_RISING_EDGE)
		{
			_timestamp_rising = std::chrono::high_resolution_clock::now();
		}
		else if (evnt == GPIOEVENT_EVENT_FALLING_EDGE)
		{
			_timestamp_falling = std::chrono::high_resolution_clock::now();

			std::chrono::duration<double> delta_t = _timestamp_falling - _timestamp_rising;

			// vitesse du son : 340m/s
			_distance = (delta_t.count() * 170000.); //* 340. /2. * 1000.
			_status = 1;
		}
	}
	
	return 0;
}

