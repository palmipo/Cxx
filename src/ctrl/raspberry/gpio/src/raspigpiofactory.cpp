#include "raspigpiofactory.h"
#include "raspigpio.h"
#include "raspigpioexception.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include "log.h"

// /dev/gpiochip0
RaspiGpioFactory::RaspiGpioFactory(const std::string & device_p)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "RaspiGpioFactory");

	// ouverture du port
	_handler = ::open(device_p.c_str(), O_RDONLY);
	if (_handler < 0)
	{
		std::stringstream ss;
		ss << "open : " << strerror(errno);
		throw RaspiGpioException(__FILE__, __LINE__, ss.str());
	}
}

RaspiGpioFactory::~RaspiGpioFactory()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "~RaspiGpioFactory");

	std::map < int32_t, RaspiGpio * >::iterator it1 = _io_map.begin();
	while (it1 != _io_map.end())
	{
		if (it1->second)
		{
			delete it1->second;
			it1->second = 0;
		}
		it1++;
	}

	// fermeture du port
	if (::close(_handler))
	{
		Log::getLogger()->error(__FILE__, __LINE__, std::strerror(errno));
	}
}

void RaspiGpioFactory::info()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "info");

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
RaspiGpio * RaspiGpioFactory::event(int32_t input_offset, int32_t event_flags, int32_t handleflags)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "event");

	RaspiGpio * in = 0;
	std::map < int32_t, int32_t >::iterator it = _event_map.find(input_offset);
	if (it != _event_map.end())
	{
		in = (RaspiGpio *)get(it->second);
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
			throw RaspiGpioException(__FILE__, __LINE__, errno);
		}

		in = new RaspiGpio(&input_offset, 1, input_event_request.fd);
		_event_map[input_offset] = input_event_request.fd;
	}

	return in;
}

RaspiGpio * RaspiGpioFactory::inputs(int32_t * pins, int32_t length)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "input");

	RaspiGpio * in = 0;
	std::map < int32_t, RaspiGpio * >::iterator it = _io_map.find(pins[0]);
	if (it != _io_map.end())
	{
		in = it->second;
	}
	else
	{
		struct gpiohandle_request input_event_request;
		memset(&input_event_request, 0, sizeof(struct gpiohandle_request));
		input_event_request.flags = GPIOHANDLE_REQUEST_INPUT;
		input_event_request.lines = length;
		for (int32_t i=0; i<length; ++i)
		{
			input_event_request.lineoffsets[i] = pins[i];
		}

		if (ioctl(_handler, GPIO_GET_LINEHANDLE_IOCTL, &input_event_request) < 0)
		{
			throw RaspiGpioException(__FILE__, __LINE__, errno);
		}

		in = new RaspiGpio(pins, length, input_event_request.fd);
		for (int32_t i=0; i<length; ++i)
		{
			_io_map[pins[i]] = in;
		}
	}

	return in;
}

RaspiGpio * RaspiGpioFactory::outputs(int32_t * pins, int32_t length)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "output");

	RaspiGpio * out = 0;
	std::map < int32_t, RaspiGpio * >::iterator it = _io_map.find(pins[0]);
	if (it != _io_map.end())
	{
		out = it->second;
	}
	else
	{
		struct gpiohandle_request output_request;
		memset(&output_request, 0, sizeof(struct gpiohandle_request));
		output_request.flags = GPIOHANDLE_REQUEST_OUTPUT;
		output_request.lines = length;
		for (int32_t i=0; i<length; ++i)
		{
			output_request.lineoffsets[i] = pins[i];
		}

		if (ioctl(_handler, GPIO_GET_LINEHANDLE_IOCTL, &output_request) < 0)
		{
			throw RaspiGpioException(__FILE__, __LINE__, errno);
		}

		out = new RaspiGpio(pins, length, output_request.fd);
		for (int32_t i=0; i<length; ++i)
		{
			_io_map[pins[i]] = out;
		}
	}

	return out;
}
