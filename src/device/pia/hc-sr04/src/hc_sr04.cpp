#include "hc_sr04.h"
#include "pia.h"
#include "tempo.h"
#include "log.h"
#include <sstream>
#include <chrono>

HC_SR04::HC_SR04(PIA * OUT_PIN)
: _distance(0)
, _status(0)
, _out(OUT_PIN)
{}

HC_SR04::~HC_SR04()
{}

void HC_SR04::start()
{
	_status = 1;

	_out->write(1);

	Tempo::microsecondes(10);

	_out->write(0);
}

int32_t HC_SR04::isBusy()
{
	return _status;
}

uint64_t HC_SR04::distance()
{
	return _distance;
}

void HC_SR04::setTimeRising(uint64_t time)
{
	_timestamp_rising = time;
}

void HC_SR04::setTimeFalling(uint64_t time)
{
	_timestamp_falling = time;
	_status = 0;
}

