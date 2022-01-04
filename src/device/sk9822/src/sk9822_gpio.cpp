#include "sk9822_gpio.h"
#include <sstream>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <linux/gpio.h>
#include <thread>
#include <sys/ioctl.h>
#include <unistd.h>
SK9822_gpio::SK9822_gpio(const std::string & device_p, int32_t cki, int32_t sdi)
: SK9822_io()
, _handler(-1)
{
	_handler = ::open(device_p.c_str(), O_RDONLY);
	if (_handler < 0)
	{
		std::stringstream ss;
		ss << "cant not open " << device_p << " ; eror : " << strerror(errno);
		std::perror(ss.str().c_str());
	}

	struct gpiohandle_request output_request;
	memset(&output_request, 0, sizeof(struct gpiohandle_request));
	output_request.flags = GPIOHANDLE_REQUEST_OUTPUT;
	output_request.lines = 2;
	output_request.lineoffsets[0] = cki;
	output_request.lineoffsets[1] = sdi;

	if (ioctl(_handler, GPIO_GET_LINEHANDLE_IOCTL, &output_request) < 0)
	{
		std::strerror(errno);
	}
}

SK9822_gpio::~SK9822_gpio()
{
	if (::close(_handler))
	{
		std::strerror(errno);
	}
}

void SK9822_gpio::write_bit(uint8_t bit)
{
	struct gpiohandle_data output_values;
	output_values.values[0] = 0;
	output_values.values[1] = bit;
	if (ioctl(_handler, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &output_values) < 0)
	{
		std::strerror(errno);
	}
	
	// tempo clk=0
	std::this_thread::sleep_for(std::chrono::microseconds(1));

	output_values.values[0] = 1;
	if (ioctl(_handler, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &output_values) < 0)
	{
		std::strerror(errno);
	}

	// tempo clk=1
	std::this_thread::sleep_for(std::chrono::microseconds(1));
}
