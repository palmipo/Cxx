#include "hc1632.h"
#include "badmintonfactory.h"
#include "log.h"
#include "gpioexception.h"
#include <chrono>
#include <thread>

void fct_scrute(BatmintonFactory * factory, int32_t * fin)
{
//	Log::getLogger()->debug(__FILE__, __LINE__, "scrute 1");
	while(fin)
	{
//		Log::getLogger()->debug(__FILE__, __LINE__, "scrute 2");
		factory->scrute(1000);
	}
//	Log::getLogger()->debug(__FILE__, __LINE__, "scrute 3");
}

int main(int argc, char ** argv)
{
	int32_t fin = 0;

	try
	{
		BatmintonFactory factory("/dev/gpiochip0");
		std::thread t(fct_scrute, &factory, &fin);
		t.detach();

		while(1)
		{
			if (factory.status() > 0)
			{
				factory.majAffichage();
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
