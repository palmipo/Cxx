#include "is31fl3731.h"
#include "raspii2c.h"
#include "log.h"
#include <thread>

int main(int argc, char **argv)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "*************** DEBUT ***************");

	RaspiI2C bus("/dev/i2c-1");
	IS31FL3731 pHAT_HD(0, &bus);
	for (int32_t i=0; i<8; ++i)
	{
		pHAT_HD.led(0, i, 1, 1, 0x0F);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	Log::getLogger()->debug(__FILE__, __LINE__, "*************** FIN ***************");
	std::this_thread::sleep_for(std::chrono::seconds(10));

	return 0;
}

