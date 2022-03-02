#include "phat_enviro.h"
#include "raspigpiofactory.h"
#include "raspigpio.h"
#include "raspipia.h"
#include "tcs34725.h"
#include "raspii2c.h"
#include "tempo.h"
#include "log.h"
#include <thread>
#include <sstream>

int main(int argc, char **argv)
{
	RaspiGpioFactory factory("/dev/gpiochip0");
	int32_t pin = 4;
	RaspiGpio *io = factory.outputs(&pin, 1);
	RaspiPia pia(io);

	Tempo::secondes(5);

	PHatEnviro pHat(&pia);

	Tempo::secondes(5);

	pHat.setLed(1);

	Tempo::secondes(5);

	RaspiI2C i2c("/dev/i2c-1");
	TCS34725 capteur_couleur(&i2c);

	std::stringstream ss;
	ss << (uint32_t)capteur_couleur.id();
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	
	pHat.setLed(1);
	
	return 0;
}
