#include "hc1632.h"
#include "badmintonfactory.h"
#include "log.h"
#include "gpioexception.h"
#include <chrono>
#include <thread>

static void scrute(BatmintonFactory * factory, int32_t * fin)
{
	while(!fin)
	{
		factory->scrute(1000);
	}
}

int main(int argc, char ** argv)
{
	int32_t fin = 0;

	try
	{
		BatmintonFactory factory("/dev/gpiochip0");
		std::thread t(scrute, &factory, &fin);
		t.detach();

		while(1)
		{
			if (factory.status() > 0)
			{
				factory.majAffichage();
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}
		
		fin = 1;
		std::this_thread::sleep_for(std::chrono::seconds(5));
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
