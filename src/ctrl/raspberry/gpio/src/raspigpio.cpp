#include "raspigpio.h"
#include "raspigpioexception.h"

#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "log.h"

RaspiGpio::RaspiGpio(int32_t * pins, int32_t length, int32_t handler)
: PollDevice(Device::GPIO, handler)
, _pins_number(new int32_t[length])
, _pins_length(length)
{
	for (int32_t i=0; i<length; ++i)
	{
		_pins_number[i] = pins[i];
	}
}

RaspiGpio::~RaspiGpio()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "~RaspiGpio");

	delete[] _pins_number;

	// fermeture du port
	if (::close(_handler))
	{
		Log::getLogger()->error(__FILE__, __LINE__, std::strerror(errno));
	}
}

int32_t RaspiGpio::pinNumber() const
{
	return _pins_number[0];
}

int32_t RaspiGpio::write(uint8_t * data, int32_t length)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "write");

	struct gpiohandle_data output_values;
	for (int32_t i=0; i<length; i++)
	{
		output_values.values[i] = data[i];
	}
	
	if (ioctl(_handler, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &output_values) < 0)
	{
		throw RaspiGpioException(__FILE__, __LINE__, errno);
	}

	return length;
}

int32_t RaspiGpio::read(uint8_t * data, int32_t length)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "read");

	struct gpiohandle_data input_values;
	if (ioctl(_handler, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &input_values) < 0)
	{
		throw RaspiGpioException(__FILE__, __LINE__, errno);
	}

	for (int32_t i=0; i<length; i++)
	{
		data[i] = input_values.values[i];
	}

	return length;
}

int32_t RaspiGpio::readEvent(uint32_t * id, uint64_t * timestamp)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	struct gpioevent_data input_event_data;
	if (::read(_handler, &input_event_data, sizeof(struct gpioevent_data)) <= 0)
	{
		throw RaspiGpioException(__FILE__, __LINE__, errno);
	}

	*timestamp = input_event_data.timestamp;
	*id = input_event_data.id;
	
	return input_event_data.id;
}
