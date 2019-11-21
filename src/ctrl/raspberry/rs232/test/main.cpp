#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include "callback.h"
#include "polldevice.h"
#include "pollbuffer.h"
#include <cstdint>
#include <iostream>

int32_t fct(PollDevice * device, PollBuffer * buffer)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "callback");
}

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

int main (int argc, char **argv)
{
    try
    {
        Factory factory;
        RS232 * serial = factory.add("/dev/ttyUSB0", fct);
        serial->setConfig(B115200, 8, 'N', 2);

        factory.scrute(1000);
    }
    catch(RS232Exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
