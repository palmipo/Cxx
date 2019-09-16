#include "gpiofactory.h"
#include "gpio.h"
#include "gpioexception.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include "log.h"

GpioFactory::GpioFactory(const std::string & device_p)
: PollFactory()
{
	/*
	{
		std::stringstream ss;
		ss << "ouverture device : " << device_p;
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
	*/

	// ouverture du port
	_handler = ::open(device_p.c_str(), O_RDONLY);
	if (_handler < 0)
	{
		std::stringstream ss;
		ss << "open : " << strerror(errno);
		throw GpioException(__FILE__, __LINE__, ss.str());
	}
}

GpioFactory::~GpioFactory()
{
	//Log::getLogger()->debug(__FILE__, __LINE__, "~GpioFactory");

	std::map < int32_t, Gpio * >::iterator it = _map_io.begin();
	while (it != _map_io.end())
	{
		if (it->second)
		{
			delete it->second;
			it->second = 0;
		}
		it++;
	}

	// fermeture du port
	if (::close(_handler))
	{
		Log::getLogger()->error(__FILE__, __LINE__, std::strerror(errno));
	}
}

// GPIOEVENT_REQUEST_RISING_EDGE
// GPIOEVENT_REQUEST_FALLING_EDGE
// GPIOEVENT_REQUEST_BOTH_EDGES;
Gpio * GpioFactory::event(int32_t input_offset, int32_t event_flags)
{
	//Log::getLogger()->debug(__FILE__, __LINE__, "event");

	Gpio * in = 0;
	std::map < int32_t, int32_t >::iterator it = _map_event.find(input_offset);
	if (it != _map_event.end())
	{
		in = (Gpio *)get(it->second);
	}
	else
	{
		struct gpioevent_request input_event_request;
		memset(&input_event_request, 0, sizeof(struct gpioevent_request));
		input_event_request.lineoffset = input_offset;
		input_event_request.handleflags = GPIOHANDLE_REQUEST_INPUT;
		input_event_request.eventflags  = event_flags;
		if (ioctl(_handler, GPIO_GET_LINEEVENT_IOCTL, &input_event_request) < 0)
		{
			throw GpioException(__FILE__, __LINE__, errno);
		}

		in = new Gpio(input_offset, input_event_request.fd);
		add(in);
		_map_event[input_offset] = input_event_request.fd;
	}

	return in;
}

Gpio * GpioFactory::input(int32_t input_offset)
{
	//Log::getLogger()->debug(__FILE__, __LINE__, "input");

	Gpio * in = 0;
	std::map < int32_t, Gpio * >::iterator it = _map_io.find(input_offset);
	if (it != _map_io.end())
	{
		in = it->second;
	}
	else
	{
		struct gpiohandle_request input_event_request;
		memset(&input_event_request, 0, sizeof(struct gpiohandle_request));
		input_event_request.lineoffsets[0] = input_offset;
		input_event_request.flags = GPIOHANDLE_REQUEST_INPUT;
		input_event_request.lines = 1;

		if (ioctl(_handler, GPIO_GET_LINEHANDLE_IOCTL, &input_event_request) < 0)
		{
			throw GpioException(__FILE__, __LINE__, errno);
		}

		in = new Gpio(input_offset, input_event_request.fd);
		_map_io[input_offset] = in;
	}

	return in;
}

Gpio * GpioFactory::output(int32_t output_offset)
{
	//Log::getLogger()->debug(__FILE__, __LINE__, "output");

	Gpio * out = 0;
	std::map < int32_t, Gpio * >::iterator it = _map_io.find(output_offset);
	if (it != _map_io.end())
	{
		out = it->second;
	}
	else
	{
		struct gpiohandle_request output_request;
		memset(&output_request, 0, sizeof(struct gpiohandle_request));
		output_request.lineoffsets[0] = output_offset;
		output_request.flags = GPIOHANDLE_REQUEST_OUTPUT;
		output_request.lines = 1;

		if (ioctl(_handler, GPIO_GET_LINEHANDLE_IOCTL, &output_request) < 0)
		{
			throw GpioException(__FILE__, __LINE__, errno);
		}

		out = new Gpio(output_offset, output_request.fd);
		_map_io[output_offset] = out;
	}

	return out;
}

/*
int32_t GpioFactory::actionIn(PollDevice * device)
{
	//Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	return device->actionIn();
}

int32_t GpioFactory::actionOut(PollDevice * device)
{
	//Log::getLogger()->debug(__FILE__, __LINE__, "actionOut");

	return device->actionOut();
}

int32_t GpioFactory::actionError(PollDevice * device)
{
	//Log::getLogger()->debug(__FILE__, __LINE__, "actionError");

	return device->actionError();
}
*/
