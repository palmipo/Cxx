#include "apc220.h"
#include "rs232factory.h"
#include "rs232.h"
#include "raspigpiofactory.h"
#include "raspipia.h"

int main(int argc, char **argv)
{
	RS232Factory fact;
	RS232 * uart = fact.add(argv[1]);

	int32_t pin_set = 10;
	int32_t pin_enable = 11;

	RaspiGpioFactory gpio(argv[2]);
	RaspiGpio * out_set = gpio.outputs(&pin_set, 1);
	RaspiGpio * out_enable = gpio.outputs(&pin_enable, 1);

	RaspiPia pia_set(out_set);
	RaspiPia pia_enable(out_enable);

	APC220 radio(&pia_set, &pia_enable, uart);
	radio.getConfig();

	return 0;
}
