#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
//~ #include "callback.h"
//~ #include "polldevice.h"
//~ #include "pollbuffer.h"
#include <cstdint>
#include <thread>
#include <iostream>

static int32_t actionIn(PollDevice * device, void *)
{
	try
	{
		uint8_t data[256];
		int32_t len = device->read(data, 256);

		Log::getLogger()->debug(__FILE__, __LINE__, "callback");
		
		return len;
	}
	catch(RS232Exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	return 0;
}

int main (int argc, char **argv)
{
	try
	{
		RS232Factory factory;
		factory.setActionInCallback(actionIn, 0);

		RS232 * serial = factory.add("/dev/ttyUSB0");
		serial->setConfig(B115200, 8, 'N', 2);

		factory.scrute(1000);
		std::this_thread::sleep_for(std::chrono::minutes(2));
	}
	catch(RS232Exception & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
