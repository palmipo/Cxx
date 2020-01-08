#include "hc1632.h"
#include "badmintonfactory.h"
#include "log.h"
#include "gpioexception.h"
#include <chrono>

int main(int argc, char ** argv)
{
	int32_t fin = 0;

	try
	{
		BatmintonFactory factory("/dev/gpiochip0");

		while(!fin)
		{
			factory.scrute(1000);
			if (factory.status() > 0)
			{
				factory.majAffichage();
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
		
		fin = 1;
		return 0;
	}
	catch(GpioException e)
	{
		Log::getLogger()->error(__FILE__, __LINE__, e.what());
		fin = 1;
		return -1;
	}
	catch(...)
	{
		Log::getLogger()->error(__FILE__, __LINE__, "exception");
		fin = 1;
		return -1;
	}
}
