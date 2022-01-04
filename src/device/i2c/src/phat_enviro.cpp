#include "phat_enviro.h"
#include "gpio.h"


PHatEnviro::PHatEnviro(Gpio * gpio_led)
: _gpio_led(gpio_led)
{
	setLed(0);
}

PHatEnviro::~PHatEnviro()
{
	setLed(0);
}

void PHatEnviro::setLed(uint8_t on)
{
	_gpio_led->write(on);
}
