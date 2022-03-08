#include "phat_enviro.h"
#include "pia.h"


PHatEnviro::PHatEnviro(PIA * gpio_led)
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
