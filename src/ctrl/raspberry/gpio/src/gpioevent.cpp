#include "gpioevent.h"

GpioEvent::GpioEvent()
: _timestamp(0)
, _id(0)
{}

GpioEvent::GpioEvent(uint32_t id, uint64_t timestamp)
: _timestamp(timestamp)
, _id(id)
{}

void GpioEvent::set(uint32_t id, uint64_t timestamp)
{
	_timestamp = timestamp;
	_id = id;
}

uint64_t GpioEvent::timestamp()
{
	return _timestamp;
}

uint32_t GpioEvent::id()
{
	return _id;
}
