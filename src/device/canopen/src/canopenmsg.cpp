#include "canopenmsg.h"
#include "canopen.h"
#include "canopenbuffer.h"

CAN::CANOpenMsg::CANOpenMsg(uint8_t pdo_id, uint8_t node_id, CAN::CANOpen * interface_can)
: _pdo_id(pdo_id)
, _node_id(node_id)
, _bus_can(interface_can)
, _cyclic(0)
{}

int32_t CAN::CANOpenMsg::read(uint8_t * data, int32_t length)
{
	CANOpenBuffer buffer;
	buffer.pdo = _pdo_id;
	buffer.node_id = _node_id;
	int32_t len = _bus_can->readData(&buffer);
	return buffer.read(data, len);
}

int32_t CAN::CANOpenMsg::write(uint8_t * data, int32_t length)
{
	CANOpenBuffer buffer;
	buffer.pdo = _pdo_id+1;
	buffer.node_id = _node_id;
	int32_t len = buffer.write(data, length);
	_bus_can->writeData(&buffer);
	
	return len;
}
