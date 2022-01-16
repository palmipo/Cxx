#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include "log.h"
#include "polldevice.h"
#include <cstdint>
#include <sstream>
#include <thread>

static int32_t callback(PollDevice * device)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "callback");

	uint8_t data[256];
	int32_t len = device->read(data, 256);
	device->write(data, len);

	std::stringstream ss;
	ss << "callback : " << device->handler() << " (" << len << ") " << std::endl;
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	
	return 0;
}

void scrute(RS232Factory * factory, int32_t * fin)
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

	try
	{
		int32_t fin = 0;
		RS232Factory factory;
		factory.setActionInCallback(callback);

		std::thread t(scrute, &factory, &fin);

		RS232 * serial = factory.add(argv[1]);
		serial->setConfig(B9600, 8, 'E', 1);

		uint8_t data[] = {0, 1, 2, 3, 4};
		serial->write(data, 5); 

		std::this_thread::sleep_for(std::chrono::minutes(2));

		fin = 1;
		t.join();
	}
	catch(RS232Exception & e)
	{
		Log::getLogger()->debug(__FILE__, __LINE__, e.what());
	}

    return 0;
}
