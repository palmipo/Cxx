#include "gpiofifo.h"
#include "gpioevent.h"
#include "gpioexception.h"

#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "log.h"

GpioFifo::GpioFifo(int32_t pin_number, int32_t handler)
:Gpio(pin_number, handler)
{}

GpioFifo::~GpioFifo()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "~Gpio");
}

GpioEvent * GpioFifo::getEvent()
{
	if (_fifo.empty())
	{
		throw GpioException(__FILE__, __LINE__, "fifo vide !");
	}

	GpioEvent * buffer = _fifo.front();
	_fifo.pop();

	return buffer;
}

int32_t GpioFifo::actionIn()
{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	struct gpioevent_data input_event_data;
	if (::read(_handler, &input_event_data, sizeof(struct gpioevent_data)) <= 0)
	{
		throw GpioException(__FILE__, __LINE__, errno);
	}
	
	GpioEvent * event = new GpioEvent(input_event_data.id, input_event_data.timestamp);
	_fifo.push(event);

	return input_event_data.id;
}
