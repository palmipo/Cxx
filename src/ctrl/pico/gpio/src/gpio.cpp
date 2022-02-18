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
}

int32_t Gpio::pinNumber() const
{
	return _pin_number;
}

int32_t Gpio::write(uint8_t * data, int32_t length)
{
}

int32_t Gpio::read(uint8_t * data, int32_t length)
{
}

int32_t Gpio::readEvent(uint32_t * id, uint64_t * timestamp)
{
}
