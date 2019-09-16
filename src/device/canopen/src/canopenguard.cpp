#include "canopenguard.h"
#include "canopen.h"
#include "canopenbuffer.h"

CAN::CANOpenGuard::CANOpenGuard(uint8_t node_id, CAN::CANOpen * interface_can)
//: CAN::CANOpenFifo()
: _node_id(node_id)
, _bus_can(interface_can)
{}

int32_t CAN::CANOpenGuard::read(uint8_t * state)
{
	CANOpenBuffer buffer;// = firstOut();
	_bus_can->readData(&buffer);
	
	int32_t cpt = 0;
	uint8_t data[8];
	int32_t len = buffer.read(data, 8);
	if (len)
	{
		*state = data[cpt]; cpt += 1;
	}
	
	return len;
}
