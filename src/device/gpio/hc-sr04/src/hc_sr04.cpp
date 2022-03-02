#include "hc_sr04.h"
#include "raspigpio.h"
#include "raspigpiofactory.h"
#include "log.h"
#include <sstream>
#include <chrono>

HC_SR04::HC_SR04(RaspiGpio * OUT_PIN, RaspiGpio * IRQ_PIN)
: _distance(0.)
, _out(OUT_PIN)
, _in(IRQ_PIN)
{}

HC_SR04::~HC_SR04()
{
}

void HC_SR04::start(int32_t intervalle_500ms)
{
	_status = 0;
	_out->write(1);

	std::this_thread::sleep_for(std::chrono::microseconds(10));

	_out->write(0);
}

int32_t HC_SR04::status()
{
	return _status;
}

double HC_SR04::distance()
{
	return _distance;
}

int32_t HC_SR04::actionIn(nt32_t evnt, uint64_t time)
{
		if (evnt == GPIOEVENT_EVENT_RISING_EDGE)
		{
			_timestamp_rising = time;
		}
		else if (evnt == GPIOEVENT_EVENT_FALLING_EDGE)
		{
			//_timestamp_falling = std::chrono::high_resolution_clock::now();
			_timestamp_falling = time;

			//std::chrono::duration<double> delta_t = _timestamp_falling - _timestamp_rising;
			uint64_t delta_t = _timestamp_falling - _timestamp_rising;

			// vitesse du son : 340m/s
			//_distance = (delta_t.count() * 170000.); //* 340. /2. * 1000.
			_distance = (delta_t * 170000.); //* 340. /2. * 1000.
			_status = 1;
		}
	}
	
	return 0;
}

