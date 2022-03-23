#include "apc220.h"
#include "rs232factory.h"
#include "rs232.h"
#include "raspigpiofactory.h"
#include "raspipia.h"

int main(int argc, char **argv)
{
	RS232Factory fact;
	RS232 * uart = fact.add(argv[1]);

	// SET, EN, AUX
	int32_t pin[] = { 10, 11, 12 };

	RaspiGpioFactory gpio(argv[2]);
	RaspiGpio * out = gpio.outputs(pin, 3);

	RaspiPia pia(out);

	APC220 radio(&pia, uart);
	radio.setConfig(434000, 3, 9, 0, 0);
	radio.getConfig();

	radio.write("coucou", 6);

	uint8_t data[512];
	radio.read(data, 512);

	return 0;
}
