#include "ixxatfactory.h"
#include "sockettcp.h"
#include "socketcan.h"
#include "ixxatcanatnet.h"
#include "ixxatusbcan.h"
#include "polldevice.h"
#include "log.h"
#include <sstream>

Ixxat::Factory::Factory()
: PollFactory()
{}

Ixxat::Factory::~Factory()
{}

Ixxat::UsbCan * Ixxat::Factory::usbToCan(const std::string & interface)
{
	std::map < std::string, Device * >::iterator it = ctrlMap.find(interface);
	if (it != ctrlMap.end())
	{
		return (Ixxat::UsbCan *)it->second;
	}

	Socket::SocketCan * socket = new Socket::SocketCan();
	socket->connexion(interface);
	add(socket);
	
	Ixxat::UsbCan * ixxat = new Ixxat::UsbCan(socket);
	ctrlMap[interface] = ixxat;
	return ixxat;
}

Ixxat::CanAtNet * Ixxat::Factory::canAtNet(const std::string & addr, int16_t port, int32_t baudrate)
{
	std::map < std::string, Device * >::iterator it = ctrlMap.find(addr);
	if (it != ctrlMap.end())
	{
		return (Ixxat::CanAtNet *)it->second;
	}

	Socket::SocketTcp * socket = new Socket::SocketTcp();
	socket->connexion(addr, port);
	add(socket);
	
	Ixxat::CanAtNet * ixxat = new Ixxat::CanAtNet(socket);
	ctrlMap[addr] = ixxat;
	ixxat->init(baudrate);
	return ixxat;
}

int32_t Ixxat::Factory::actionError(PollDevice * device)
{
	if (device)
	{
		return device->actionError();
	}
	
	return 0;
}

int32_t Ixxat::Factory::actionIn(PollDevice * device)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	if (device)
	{
		return device->actionIn();
	}

	return 0;
}

int32_t Ixxat::Factory::actionOut(PollDevice * device)
{
	if (device)
	{
		return device->actionOut();
	}
	
	return 0;
}

int32_t Ixxat::Factory::actionError()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionError");

	int32_t len = 0;
	std::map < std::string, Device * >::iterator it = ctrlMap.begin();
	while (it != ctrlMap.end())
	{
		if (it->second)
		{
			len += it->second->actionError();
		}
		it++;
	}

	return len;
}

int32_t Ixxat::Factory::actionIn()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	int32_t len = 0;
	std::map < std::string, Device * >::iterator it = ctrlMap.begin();
	while (it != ctrlMap.end())
	{
		if (it->second)
		{
			len += it->second->actionIn();
		}
		it++;
	}

	return len;
}

int32_t Ixxat::Factory::actionOut()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionOut");

	int32_t len = 0;
	std::map < std::string, Device * >::iterator it = ctrlMap.begin();
	while (it != ctrlMap.end())
	{
		if (it->second)
		{
			len += it->second->actionOut();
		}
		it++;
	}

	return len;
}
