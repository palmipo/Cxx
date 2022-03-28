#include "rs232factory.h"
#include "rs232.h"
#include "rs232exception.h"
#include "log.h"
#include <cerrno>
#include <sstream>

RS232Factory::RS232Factory()
{}

RS232Factory::~RS232Factory()
{
	std::map<std::string, RS232 *>::iterator it = _port.begin();
	while (it != _port.end())
	{
		delete it->second;
		it++;
	}
}

RS232 * RS232Factory::add(const std::string & device_p)
{
	try
	{
		return get(device_p);
	}
	catch(...)
	{
		RS232 * serial = new RS232(device_p);
		_port[device_p] = serial;
		return serial;
	}
}

RS232 * RS232Factory::get(const std::string & device_p)
{
	std::map<std::string, RS232 *>::iterator it = _port.find(device_p);
	if (it != _port.end())
	{
		return it->second;
	}

	std::stringstream ss;
	ss << "device not known : " << device_p;
	throw RS232Exception(__FILE__, __LINE__, ss.str());
}

void RS232Factory::del(const std::string & device_p)
{
	std::map<std::string, RS232 *>::iterator it = _port.find(device_p);
	if (it == _port.end())
	{
		std::stringstream ss;
		ss << "device not find : " << device_p;
		throw RS232Exception(__FILE__, __LINE__, ss.str());
	}

	delete it->second;
	_port.erase(it);
}
