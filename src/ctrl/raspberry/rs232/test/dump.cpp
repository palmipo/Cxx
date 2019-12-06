#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include "log.h"
#include "callback.h"
#include "polldevice.h"
#include "pollbuffer.h"
#include <cstdint>
#include <sstream>
#include <thread>

class Factory : public RS232Factory
{
	public:
		Factory()
		{}

		virtual RS232 * add(const std::string & device, int32_t (*f)(PollDevice *, PollBuffer *))
		{
			RS232 * rs = RS232Factory::add(device);
			_clb.set(f, rs);
			return rs;
		}

		virtual int32_t actionIn(PollDevice * device)
		{
			uint8_t data[256];
			device->actionIn();
			int32_t len = device->read(data, 256);

			PollBuffer buffer;
			buffer.write(data, len);
			_clb.call(&buffer);
		}

		virtual int32_t actionOut(PollDevice * device)
		{
		}

		virtual int32_t actionError(PollDevice * device)
		{
		}

	protected:
		Callback<int32_t (*)(PollDevice *, PollBuffer *), PollDevice *, PollBuffer *> _clb;
};

void scrute(Factory * factory, int32_t * fin)
{
	while (! *fin)
	{
		factory->scrute(1000, 1, 1, 1);
	}
}

int32_t fct(PollDevice * device, PollBuffer * buffer)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "callback");
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
	Factory factory;
	std::thread t(scrute, &factory, &fin);

	try
	{
		RS232 * serial = factory.add(argv[1], fct);
		serial->setConfig(B19200, 8, 'E', 1);
	}
	catch(RS232Exception & e)
	{
		Log::getLogger()->debug(__FILE__, __LINE__, e.what());
	}

	t.join();

    return 0;
}
