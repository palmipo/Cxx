#include "gpioarray.h"
#include "gpioexception.h"

#include <sys/ioctl.h>
#include <unistd.h>
#include <sstream>
#include "log.h"

GpioArray::GpioArray(int32_t handler)
: PollDevice(handler)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "GpioArray");
}

GpioArray::~GpioArray()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "~GpioArray");

	// fermeture du port
	if (::close(_handler))
	{
		std::stringstream ss ;
		ss << errno;
		Log::getLogger()->error(__FILE__, __LINE__, ss.str());
	}
}

void GpioArray::set(int32_t i, uint8_t v)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "set");

	_values.values[i] = v;
}

uint8_t GpioArray::get(int32_t i)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "get");

	return _values.values[i];
}

void GpioArray::write()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "write");

	if (ioctl(_handler, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &_values) < 0)
	{
		throw GpioException(__FILE__, __LINE__, errno);
	}
}

void GpioArray::read()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "read");

	if (ioctl(_handler, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &_values) < 0)
	{
		throw GpioException(__FILE__, __LINE__, errno);
	}
}
