#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include "log.h"
#include "polldevice.h"
#include "pollbuffer.h"
#include <cstdint>
#include <sstream>
#include <thread>


static int32_t actionIn(PollDevice * device)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	uint8_t data[256];
	int32_t len = device->read(data, 256);

	std::stringstream ss;
	ss << "callback : " << device->handler() << " (" << len << ") " << std::endl;
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());


void scrute(Factory * factory, int32_t * fin)
{
	while (! *fin)
	{
		factory->scrute(1000);
	}
}

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		std::stringstream ss;
		ss << argv[0] << " </dev/ttyUSB0>";
		Log::getLogger()->error(__FILE__, __LINE__, ss.str());
		return -1;
	}

	int32_t fin = 0;
	RS232Factory factory;
	factory.setActionInCallback(fct);

	// creation du thread secondaire
	std::thread t(scrute, &factory, &fin);

	try
	{
		RS232 * serial = factory.add(argv[1]);
		serial->setConfig(B19200, 8, 'E', 1);
		
		// endort le thread principal pour 2 minutes
		std::this_thread::sleep_for(std::chrono::minutes(2));
	}
	catch(RS232Exception & e)
	{
		Log::getLogger()->debug(__FILE__, __LINE__, e.what());
	}

	fin = 1;
	t.join();

    return 0;
}
