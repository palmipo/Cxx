#include "hc1632.h"
#include "badmintonfactory.h"
#include "log.h"
#include "gpioexception.h"

int main(int argc, char ** argv)
{
	try
	{
		BatmintonFactory factory("/dev/gpiochip0");

		while(1)
		{
			factory.scrute(1000);
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
