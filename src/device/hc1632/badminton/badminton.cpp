#include "hc1632.h"
#include "badmintonfactory.h"
#include "log.h"
#include "gpioexception.h"
#include <chrono>

int main(int argc, char ** argv)
{
	try
	{
		BatmintonFactory factory("/dev/gpiochip0");

		int32_t pin = 0;
		int32_t majDemandee = 0;
		//~ std::chrono::time_point<std::chrono::high_resolution_clock> t0 = std::chrono::high_resolution_clock::now();
		while(1)
		{
			//~ if (majDemandee)
			//~ {
				//~ Log::getLogger()->error(__FILE__, __LINE__, "maj");
				//~ std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - t0;
				//~ if (elapsed.count() > 1)
				//~ {
					//~ factory.majAffichage(10);
					//~ pin = 0;
					//~ majDemandee = 0;
					//~ Log::getLogger()->error(__FILE__, __LINE__, "affichage");
				//~ }
			//~ }
			if (factory.scrute(1000) > 0)
			//~ if (!majDemandee)
			{
				factory.majAffichage(10);
				//~ majDemandee = 1;
				//~ t0 = std::chrono::high_resolution_clock::now();
				Log::getLogger()->error(__FILE__, __LINE__, "majDemandee");
			}
		}
		
		return 0;
	}
	catch(GpioException e)
	{
		Log::getLogger()->error(__FILE__, __LINE__, e.what());
		return -1;
	}
	catch(...)
	{
		Log::getLogger()->error(__FILE__, __LINE__, "exception");
		return -1;
	}
}
