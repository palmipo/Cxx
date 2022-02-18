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

// /dev/gpiochip0
GpioFactory::GpioFactory(const std::string & device_p)
: PollFactory()
{
}

GpioFactory::~GpioFactory()
{
}

void GpioFactory::info()
{
}

Gpio * GpioFactory::event(int32_t input_offset, int32_t event_flags, int32_t handleflags)
{
}

Gpio * GpioFactory::input(int32_t input_offset)
{
}

//~ Gpio * GpioFactory::inputs(int32_t * input_offset, int32_t length)
//~ {
//~ }

Gpio * GpioFactory::output(int32_t output_offset)
{
}

//~ Gpio * GpioFactory::outputs(int32_t * output_offset, int32_t length)
//~ {
//~ }
