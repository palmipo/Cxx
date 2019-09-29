#include "gpio.h"
#include "gpioevent.h"
#include "gpioexception.h"

#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "log.h"

Gpio::Gpio(int32_t pin_number, int32_t handler)
: PollDevice(handler)
, _pin_number(pin_number)
, _evnt(new GpioEvent())
{}

Gpio::~Gpio()
{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "~Gpio");

	delete _evnt;

	// fermeture du port
	if (::close(_handler))
	{
		Log::getLogger()->error(__FILE__, __LINE__, std::strerror(errno));
	}
}

int32_t Gpio::pinNumber() const
{
	return _pin_number;
}

int32_t Gpio::write(uint8_t * data, int32_t length)
{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "write");

	struct gpiohandle_data output_values;
	for (int32_t i=0; i<length; ++i)
	{
		output_values.values[i] = data[i];
	}
	if (ioctl(_handler, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &output_values) < 0)
	{
		throw GpioException(__FILE__, __LINE__, errno);
	}

	return output_values.values[0];
}

int32_t Gpio::read(uint8_t * data, int32_t length)
{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "read");

	struct gpiohandle_data input_values;
	if (ioctl(_handler, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &input_values) < 0)
	{
		throw GpioException(__FILE__, __LINE__, errno);
	}

	return input_values.values[0];
}

GpioEvent * Gpio::getEvent()
{
	return _evnt;
}

int32_t Gpio::actionError()
{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "actionError");

	return 0;
}

int32_t Gpio::actionIn()
{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	struct gpioevent_data input_event_data;
	if (::read(_handler, &input_event_data, sizeof(struct gpioevent_data)) <= 0)
	{
		throw GpioException(__FILE__, __LINE__, errno);
	}

	_evnt->set(input_event_data.id, input_event_data.timestamp);
	return input_event_data.id;
}

int32_t Gpio::actionOut()
{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "actionOut");

	return 0;
}
