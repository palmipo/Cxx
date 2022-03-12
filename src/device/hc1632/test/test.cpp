#include "hc1632.h"
#include "raspigpiofactory.h"
#include "raspigpio.h"
#include "raspipia.h"

int main(int argc, char **argv)
{
	int32_t DATA_PIN = 7;
	int32_t CLK_PIN = 11;
	int32_t CS_PIN = 25;

	RaspiGpioFactory gpio_fact("/dev/gpiochip0");

	RaspiGpio * data = gpio_fact.outputs(&DATA_PIN, 1);
	RaspiGpio * clk = gpio_fact.outputs(&CLK_PIN, 1);
	RaspiGpio * cs = gpio_fact.outputs(&CS_PIN, 1);

	RaspiPia pia_data(data);
	RaspiPia pia_clk(clk);
	RaspiPia pia_cs(cs);

	HC1632 afficheur(&pia_data, &pia_clk, &pia_cs, 1);

	return 0;
}

