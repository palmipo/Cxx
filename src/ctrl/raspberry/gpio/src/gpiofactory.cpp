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
	Log::getLogger()->debug(__FILE__, __LINE__, "GpioFactory");

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
	Log::getLogger()->debug(__FILE__, __LINE__, "~GpioFactory");

	std::map < int32_t, Gpio * >::iterator it = _io_map.begin();
	while (it != _io_map.end())
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

void GpioFactory::info()
{
	struct gpiochip_info cinfo;
	ioctl(_handler, GPIO_GET_CHIPINFO_IOCTL, &cinfo);
	{
		std::stringstream ss;
		ss << "GPIO chip: " << cinfo.name << ", " << cinfo.label << ", " << cinfo.lines << " GPIO lines";
		Log::getLogger()->info(__FILE__, __LINE__, ss.str());
	}

	struct gpioline_info linfo;
	ioctl(_handler, GPIO_GET_LINEINFO_IOCTL, &linfo);
	{
		std::stringstream ss;
		ss << "line_offset : " << linfo.line_offset<< ", flags : " << linfo.flags << ", name : " << linfo.name << ", consumer : " << linfo.consumer;
		Log::getLogger()->info(__FILE__, __LINE__, ss.str());
	}
}

// GPIOHANDLE_REQUEST_INPUT
// GPIOHANDLE_REQUEST_OUTPUT
// GPIOHANDLE_REQUEST_ACTIVE_LOW
// GPIOHANDLE_REQUEST_OPEN_DRAIN
// GPIOHANDLE_REQUEST_OPEN_SOURCE

// GPIOEVENT_REQUEST_RISING_EDGE
// GPIOEVENT_REQUEST_FALLING_EDGE
// GPIOEVENT_REQUEST_BOTH_EDGES;
Gpio * GpioFactory::event(int32_t input_offset, int32_t event_flags, int32_t handleflags)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "event");

	Gpio * in = 0;
	std::map < int32_t, int32_t >::iterator it = _event_map.find(input_offset);
	if (it != _event_map.end())
	{
		in = (Gpio *)get(it->second);
	}
	else
	{
		struct gpioevent_request input_event_request;
		memset(&input_event_request, 0, sizeof(struct gpioevent_request));
		input_event_request.lineoffset = input_offset;
		input_event_request.handleflags = handleflags;
		input_event_request.eventflags  = event_flags;
		if (ioctl(_handler, GPIO_GET_LINEEVENT_IOCTL, &input_event_request) < 0)
		{
			throw GpioException(__FILE__, __LINE__, errno);
		}

		in = new Gpio(input_offset, input_event_request.fd);
		add(in);
		_event_map[input_offset] = input_event_request.fd;
	}

	return in;
}

Gpio * GpioFactory::input(int32_t input_offset)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "input");

	Gpio * in = 0;
	std::map < int32_t, Gpio * >::iterator it = _io_map.find(input_offset);
	if (it != _io_map.end())
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
		_io_map[input_offset] = in;
	}

	return in;
}

Gpio * GpioFactory::output(int32_t output_offset)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "output");

	Gpio * out = 0;
	std::map < int32_t, Gpio * >::iterator it = _io_map.find(output_offset);
	if (it != _io_map.end())
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
		_io_map[output_offset] = out;
	}

	return out;
}
