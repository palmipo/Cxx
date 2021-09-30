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
	uint8_t data[1];
	data[0] = on;
	_gpio_led->write(data, 1);
}
