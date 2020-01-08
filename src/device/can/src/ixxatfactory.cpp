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
	return device->actionError();
}

int32_t Ixxat::Factory::actionIn(PollDevice * device)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	int32_t len = 0;
	std::map < std::string, Device * >::iterator it = ctrlMap.begin();
	while (it != ctrlMap.end())
	{
		if (device->handler() == it->second->handler())
		{
			len = it->second->actionIn();
		}
		it++;
	}

	return len;
}

int32_t Ixxat::Factory::actionOut(PollDevice * device)
{
	return device->actionOut();
}
