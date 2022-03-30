#include "ada1334.h"
#include "tcs34725.h"
#include "ctrli2c.h"
#include "i2cexception.h"
#include "log.h"
#include "ctrlpia.h"
#include <sstream>
#include <thread>
#include <iomanip>

ADA1334::ADA1334(CtrlPIA * led, CtrlI2C * i2c_bus)
: _i2c(i2c_bus)
, _led(led)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "ADA1334");

	_led->write(1);
	_capteur_lumiere = new TCS34725(_i2c);

	uint8_t AIEN = 1;
	double ATIME = 100.;
	double WTIME = 2.4;
	uint8_t WLONG = 0;
	uint8_t AGAIN = 1;
	uint8_t APERS = 0;
	_capteur_lumiere->on(AIEN, ATIME, WTIME, WLONG, AGAIN, APERS);
	_capteur_lumiere->setClearInterruptThreshold(APERS, 100, -100);
}

ADA1334::~ADA1334()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "~ADA1334");

	_led->write(0);

	_capteur_lumiere->off();
	delete _capteur_lumiere;
}

void ADA1334::led(uint8_t on)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "led");

	_led->write(on ? 1 : 0);
}

int32_t ADA1334::event()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	uint16_t c, r, g, b;
	_capteur_lumiere->readChannels(&c, &r, &g, &b);

	_capteur_lumiere->clearChannelInterruptClear();

	std::stringstream ss_color;
	ss_color << "Clear : " << c << ", Red : " << r << ", Green : " << g << ", Blue : " << b;
	Log::getLogger()->debug(__FILE__, __LINE__, ss_color.str());
}

