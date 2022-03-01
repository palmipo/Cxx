#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include "log.h"
#include "tempo.h"
#include "pollfactory.h"
#include <cstdint>
#include <sstream>
#include <thread>


int32_t actionIn(PollDevice * device, void *)
{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	uint8_t data[256];
	int32_t len = device->read(data, 256);

	std::stringstream ss;
	ss << "callback : " << device->handler() << " (" << len << ") " << std::endl;
	Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	
	return len;
}

void examiner(PollFactory * factory, int32_t * fin)
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

		RS232Factory uart_factory;
		RS232 * serial = uart_factory.add(argv[1]);
		serial->setConfig(B19200, 8, 'E', 1);

		PollFactory poll_factory;
		poll_factory.setActionInCallback(actionIn, 0);
		poll_factory.add(serial->handle());

		// creation du thread secondaire
		int32_t fin = 0;
		std::thread t(examiner, &poll_factory, &fin);

		// endort le thread principal pour 2 minutes
		Tempo::minutes(2);

		fin = 1;
		t.join();
	}
	catch(RS232Exception & e)
	{
		Log::getLogger()->debug(__FILE__, __LINE__, e.what());
	}

	return 0;
}
