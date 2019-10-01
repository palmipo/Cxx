#include "rs232factory.h"
#include "rs232.h"
#include "rs232fifo.h"
#include "rs232exception.h"
#include "log.h"
#include <cerrno>
#include <sstream>

RS232Factory::RS232Factory()
: PollFactory()
{}

RS232Factory::~RS232Factory()
{}

RS232 * RS232Factory::add(const std::string & device_p)
{
    try
	{
		return get(device_p);
	}
	catch(...)
    {
		RS232 * serial = new RS232(device_p);
		if (serial)
		{
			_port[device_p] = serial->handler();
			PollFactory::add(serial);
			return serial;
		}
    }
}

RS232Fifo * RS232Factory::addFifo(const std::string & device_p)
{
    try
	{
		return (RS232Fifo *)get(device_p);
	}
	catch(...)
    {
		RS232Fifo * serial = new RS232Fifo(device_p);
		if (serial)
		{
			_port[device_p] = serial->handler();
			PollFactory::add(serial);
			return serial;
		}
    }
}

RS232 * RS232Factory::get(const std::string & device_p)
{
    std::map<std::string, int32_t>::iterator it = _port.find(device_p);
    if (it != _port.end())
    {
        return (RS232 *)PollFactory::get(it->second);
    }

	std::stringstream ss;
	ss << "device not find : " << device_p;
	throw RS232Exception(__FILE__, __LINE__, ss.str());
}

void RS232Factory::del(const std::string & device_p)
{
    std::map<std::string, int32_t>::iterator it = _port.find(device_p);
    if (it != _port.end())
    {
        PollFactory::del(it->second);
		_port.erase(it);
    }

	std::stringstream ss;
	ss << "device not find : " << device_p;
	throw RS232Exception(__FILE__, __LINE__, ss.str());
}

//~ int32_t RS232Factory::actionIn(PollDevice* device)
//~ {
    //~ return device->actionIn();
//~ }

//~ int32_t RS232Factory::actionOut(PollDevice* device)
//~ {
    //~ return device->actionOut();
//~ }

//~ int32_t RS232Factory::actionError(PollDevice* device)
//~ {
    //~ return device->actionError();
//~ }
