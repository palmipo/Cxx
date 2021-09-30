#include "is31fl3731.h"
#include "raspii2c.h"
#include "log.h"
#include <thread>

int main(int argc, char **argv)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "*************** DEBUT ***************");

	RaspiI2C bus("/dev/i2c-1");
	TCS3472 pHAT_Enviro(0, &bus);

	pHAT_HD.led(1);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	pHAT_HD.led(0);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	Log::getLogger()->debug(__FILE__, __LINE__, "*************** FIN ***************");

	return 0;
}

