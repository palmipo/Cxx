#include "gpiofactory.h"
#include "gpio.h"
#include "gpioexception.h"
#include "log.h"

#include <linux/gpio.h>
#include <sstream>

int main(int argc, char **argv)
{
	try
	{
	GpioFactory factory("/dev/gpiochip0");
	
	uint8_t valeur = 1;
	factory.output(5)->write(&valeur, 1);
	factory.output(6)->write(&valeur, 1);
	factory.output(7)->write(&valeur, 1);
	factory.output(8)->write(&valeur, 1);
	factory.output(9)->write(&valeur, 1);
	factory.output(11)->write(&valeur, 1);
	factory.output(12)->write(&valeur, 1);
	factory.output(13)->write(&valeur, 1);
	factory.output(17)->write(&valeur, 1);
	factory.output(18)->write(&valeur, 1);
	factory.output(19)->write(&valeur, 1);
	factory.output(22)->write(&valeur, 1);
	factory.output(25)->write(&valeur, 1);
	factory.output(27)->write(&valeur, 1);
	

	factory.event(10, GPIOEVENT_REQUEST_BOTH_EDGES);
//	factory.event(16, GPIOEVENT_REQUEST_BOTH_EDGES);
//	factory.event(23, GPIOEVENT_REQUEST_FALLING_EDGE);
//	factory.event(24, GPIOEVENT_REQUEST_FALLING_EDGE);

	//while(1)
	{
		int32_t etat = factory.scrute(1000);

		if (etat & GPIOEVENT_EVENT_RISING_EDGE)
			fprintf(stdout, " RISING");

		if (etat & GPIOEVENT_EVENT_FALLING_EDGE)
			fprintf(stdout, " FALLING");

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
