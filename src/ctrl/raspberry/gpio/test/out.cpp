#include "gpiofactory.h"
#include "gpio.h"
#include "gpioexception.h"
#include "log.h"

#include <thread>

int main(int argc, char **argv)
{
	try
	{
		GpioFactory factory("/dev/gpiochip0");

		int32_t PIN[] = { 18, 17, 27, 23, 22, 24, 10, 25, 9, 8, 11, 7, 5, 12, 6, 13 };
		Gpio * out = factory.outputs(PIN, 16);

		uint8_t valeur[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		out->write(valeur, 16);

		int32_t i=0;
		while(i<10)
		{
			uint8_t val = random() % 7;
			valeur[val%16] = val % 1;
			out->write(valeur, 16);
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			i += 1;
		}
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
