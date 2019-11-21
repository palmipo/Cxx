#include "canopensync.h"
#include "canopen.h"
#include "canopenbuffer.h"

CAN::CANOpenSYNC::CANOpenSYNC(CAN::CANOpen * interface_can)
: _bus_can(interface_can)
{}

void CAN::CANOpenSYNC::sendSync()
{
	CANOpenBuffer buffer;
	buffer.pdo_id = 0x1;
	buffer.node_id = 0;
	_bus_can->writeData(&buffer);
}
