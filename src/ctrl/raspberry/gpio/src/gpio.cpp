#include "gpio.h"
//~ #include "gpioevent.h"
#include "gpioexception.h"

#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "log.h"

Gpio::Gpio(int32_t pin_number, int32_t handler)
: PollDevice(handler)
, _pin_number(pin_number)
{}

Gpio::~Gpio()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "~Gpio");

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

void Gpio::write(uint8_t data)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "write");

	struct gpiohandle_data output_values;
	output_values.values[0] = data;
	if (ioctl(_handler, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &output_values) < 0)
	{
		throw GpioException(__FILE__, __LINE__, errno);
	}
}

int32_t Gpio::read()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "read");

	struct gpiohandle_data input_values;
	if (ioctl(_handler, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &input_values) < 0)
	{
		throw GpioException(__FILE__, __LINE__, errno);
	}

	return input_values.values[0];
}

int32_t Gpio::readEvent(uint32_t *id, uint64_t *timestamp)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	struct gpioevent_data input_event_data;
	if (::read(_handler, &input_event_data, sizeof(struct gpioevent_data)) <= 0)
	{
		throw GpioException(__FILE__, __LINE__, errno);
	}

	*timestamp = input_event_data.timestamp;
	*id = input_event_data.id;
	
	return input_event_data.id;
}
