#include "apc220.h"
#include "rs232factory.h"
#include "rs232.h"
#include "gpio_mod.h"

int main(int argc, char **argv)
{
	RS232Factory fact;
	RS232 * uart = fact.addSerialConnection(argv[1]);

	GPIO_MOD gpio(argv[2]);

	APC220 radio(22, 27, uart, &gpio);
	radio.getConfig();

	return 0;
}
