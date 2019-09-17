#include "lumiere.h"
#include "raspii2c.h"
#include "i2cexception.h"
#include "gpioexception.h"
#include "log.h"
#include <sstream>
#include <thread>
#include <iomanip>

int main(int argc, char **argv)
{
	try
	{
		RaspiI2C i2c_bus("/dev/i2c-1");
		Lumiere capteur("/dev/gpiochip0", 18, 4, &i2c_bus);

		int32_t cpt=0;
		while(cpt < 60)
		{
			capteur.scrute(1000);
			++cpt;
		}
	}
	catch(I2CException e)
	{
		Log::getLogger()->error(__FILE__, __LINE__, e.what());
	}
	catch(GpioException e)
	{
		Log::getLogger()->error(__FILE__, __LINE__, e.what());
	}
	catch(...)
	{
		Log::getLogger()->error(__FILE__, __LINE__, "exception");
	}

	return 0;
}
