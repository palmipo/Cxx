#include "lumiere.h"
#include "tcs34725.h"
#include "i2cexception.h"
#include "log.h"
#include "gpio.h"
#include <sstream>
#include <thread>
#include <iomanip>

Lumiere::Lumiere(const std::string & gpio_dev, int32_t led, int32_t irq, I2C * i2c_bus)
: GpioFactory(gpio_dev)
, LED_PIN(led)
, IRQ_PIN(irq)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "Lumiere");

	Gpio * gpio = output(LED_PIN);
	uint8_t valeur = 1;
	gpio->write(&valeur, 1);
	
	event(IRQ_PIN, GPIOEVENT_REQUEST_BOTH_EDGES, GPIOHANDLE_REQUEST_OPEN_DRAIN);

	capteur_lumiere = new TCS34725(i2c_bus);

	uint8_t AIEN = 1;
	double ATIME = 100.;
	double WTIME = 2.4;
	uint8_t WLONG = 0;
	uint8_t AGAIN = 1;
	capteur_lumiere->on(AIEN, ATIME, WTIME, WLONG, AGAIN);
	capteur_lumiere->setClearInterruptThreshold(0, 1000, 0xFFFF-1000);
}

Lumiere::~Lumiere()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "~Lumiere");

	capteur_lumiere->off();
	delete capteur_lumiere;

	Gpio * gpio = output(LED_PIN);
	uint8_t valeur = 0;
	gpio->write(&valeur, 1);
}


int32_t Lumiere::actionIn(PollDevice * device)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	if (device->actionIn())
	{
		uint16_t c, r, g, b;
		capteur_lumiere->readChannels(&c, &r, &g, &b);
		capteur_lumiere->clearChannelInterruptClear();

		std::stringstream ss_color;
		ss_color << "Clear : " << c << ", Red : " << r << ", Green : " << g << ", Blue : " << b;
		Log::getLogger()->debug(__FILE__, __LINE__, ss_color.str());
	}
}

int32_t Lumiere::actionOut(PollDevice * device)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionOut");

	return device->actionOut();
}

int32_t Lumiere::actionError(PollDevice * device)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionError");

	return device->actionError();
}
