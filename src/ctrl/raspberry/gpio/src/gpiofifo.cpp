#include "gpiofifo.h"
#include "gpio.h"
#include "gpioevent.h"
#include "gpioexception.h"

#include "log.h"

GpioFifo::GpioFifo(const std::string & device_p)
: GpioFactory(device_p)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "GpioFifo");
}

GpioFifo::~GpioFifo()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "~GpioFifo");
}

int32_t GpioFifo::actionIn(PollDevice* dev)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	Gpio * io = (Gpio*)dev;
	uint32_t id;
	uint64_t timestamp;
	io->readEvent(&id, &timestamp);
	
	GpioEvent * event = new GpioEvent(id, timestamp);
	_fifo.push(event);

	return 0;
}
