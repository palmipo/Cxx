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

CAN::CANOpen * CAN::CANOpenFactory::canAtNet(uint16_t node_id, const std::string & addr, int16_t port, int32_t baud_rate)
{
	Socket::SocketTcpFifo * socket = new Socket::SocketTcpFifo();
	socket->connexion(addr, port);
	add(socket);
	
	Ixxat::CanAtNet * ixxat = new Ixxat::CanAtNet(socket);
	
	CAN::CANOpen * canopen = new CANOpen(node_id, ixxat);
	ctrlMap[addr] = canopen;

	ixxat->init(baud_rate);

	return canopen;
}

CAN::CANOpen * CAN::CANOpenFactory::usbToCan(uint16_t node_id, const std::string & iface)
{
	Socket::SocketCan * socket = new Socket::SocketCan();
	socket->connexion(iface);
	add(socket);
	
	Ixxat::UsbCan * ixxat = new Ixxat::UsbCan(socket);
	
	CAN::CANOpen * canopen = new CANOpen(node_id, ixxat);
	ctrlMap[iface] = canopen;

	return canopen;
}

int32_t CAN::CANOpenFactory::actionError(PollDevice * device)
{
	return device->actionError();
}

int32_t CAN::CANOpenFactory::actionIn(PollDevice * device)
{
	// lecture sur le device
	// device->actionIn();
	
	// uint8_t data[512];
	// int32_t len = device->read(data, 512);
	
	//~ /!\ test
	// envoie aux classes Modbus et CANOpen les donnees du controleur
	std::map < std::string, Device * >::iterator it = ctrlMap.begin();
	while (it != ctrlMap.end())
	{
		if (device->handler() == it->second->handler())
		{
			it->second->actionIn();
		}
		it++;
	}
}

int32_t CAN::CANOpenFactory::actionOut(PollDevice * device)
{
	return device->actionOut();
}
