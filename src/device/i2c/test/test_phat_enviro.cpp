#include "phat_enviro.h"
#include "gpiofactory.h"
#include "gpio.h"
#include "tcs34725.h"
#include "raspii2c.h"
#include "log.h"
#include <thread>
#include <sstream>

int main(int argc, char **argv)
{
	GpioFactory factory("/dev/gpiochip0");
	Gpio *io = factory.output(4);

	std::this_thread::sleep_for(std::chrono::seconds(5));

	PHatEnviro pHat(io);

	std::this_thread::sleep_for(std::chrono::seconds(5));

	pHat.setLed(1);

	std::this_thread::sleep_for(std::chrono::seconds(5));

	RaspiI2C i2c("/dev/i2c-1");
	TCS34725 capteur_couleur(&i2c);
	std::stringstream ss;
	ss << (uint32_t)capteur_couleur.id();
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	
	//~ capteur_couleur.on(0, 0, 1, 1);
	
	return 0;
}
