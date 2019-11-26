#include "ixxatfactory.h"
#include "sockettcp.h"
#include "ixxatcanatnet.h"
// #include "ixxatusbcan.h"
#include "polldevice.h"
// #include "towerdevice.h"

Ixxat::Factory::Factory()
: PollFactory()
{}

Ixxat::Factory::~Factory()
{}

// Ixxat::UsbCan * Ixxat::Factory::usbToCan(const std::string & interface)
// {
	// Socket::SocketCan * socket = new Socket::SocketCan();
	// socket->connexion(interface);
	// add(socket);
	
	// Ixxat::UsbCan * ixxat = new Ixxat::UsbCan(socket);
	// ixxat->connexion(interface);
	// add(ixxat);
	// return ixxat;
// }

Ixxat::CanAtNet * Ixxat::Factory::canAtNet(const std::string & addr, int16_t port)
{
	Socket::SocketTcp * socket = new Socket::SocketTcp();
	socket->connexion(addr, port);
	add(socket);
	
	Ixxat::CanAtNet * ixxat = new Ixxat::CanAtNet(5, socket);
	ctrlMap[addr] = ixxat;
	return ixxat;
}

int32_t Ixxat::Factory::actionError(PollDevice * device)
{
	return device->actionError();
}

int32_t Ixxat::Factory::actionIn(PollDevice * device)
{
	int32_t len = 0;
	std::map < std::string, Device * >::iterator it = ctrlMap.begin();
	while (it != ctrlMap.end())
	{
		if (device->handler() == it->second->handler())
		{
			len = it->second->actionIn();
		}
		else
		{
			it++;
		}
	}

	return len;
}

int32_t Ixxat::Factory::actionOut(PollDevice * device)
{
	return device->actionOut();
}
