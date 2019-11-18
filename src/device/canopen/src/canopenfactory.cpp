#include "canopenfactory.h"
#include "socketcan.h"
#include "sockettcpfifo.h"
#include "ixxatcanatnet.h"
#include "ixxatusbcan.h"
#include "canopen.h"

CAN::CANOpenFactory::CANOpenFactory()
: PollFactory()
{}

CAN::CANOpenFactory::~CANOpenFactory()
{}

CAN::CANOpen * CAN::CANOpenFactory::canAtNet(const std::string & addr, int16_t port, int32_t baud_rate)
{
	Socket::SocketTcpFifo * socket = new Socket::SocketTcpFifo();
	socket->connexion(addr, port);
	add(socket);
	
	Ixxat::CanAtNet * ixxat = new Ixxat::CanAtNet(5, socket);
	ixxat->init(baud_rate);
	
	CAN::CANOpen * canopen = new CANOpen(5, ixxat, socket);
	return canopen;
}

CAN::CANOpen * CAN::CANOpenFactory::usbToCan(const std::string & iface)
{
	Socket::SocketCan * socket = new Socket::SocketCan();
	socket->connexion(iface);
	add(socket);
	
	Ixxat::UsbCan * ixxat = new Ixxat::UsbCan(5, socket);
	
	CAN::CANOpen * canopen = new CANOpen(5, ixxat, socket);
	return canopen;
}

int32_t CAN::CANOpenFactory::actionError(PollDevice * device)
{
	return device->actionError();
}

int32_t CAN::CANOpenFactory::actionIn(PollDevice * device)
{
	// lecture sur le device
	device->actionIn();
	
	uint8_t data[512];
	int32_t len = device->read(data, 512);
	
	//~ /!\ test
	// envoie aux classes Modbus et CANOpen les donnees du controleur
	std::map < std::string, TowerDevice * >::iterator it = ctrlMap.begin();
	while (it != ctrlMap.end())
	{
		if (device->handler() == it->second->handler())
		{
			it->second->actionIn(data, len);
		}
		else
		{
			it++;
		}
	}
}

int32_t CAN::CANOpenFactory::actionOut(PollDevice * device)
{
	return device->actionOut();
}
