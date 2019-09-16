#include "canopenbuffer.h"
#include <cstring>


CAN::CANOpenBuffer::CANOpenBuffer()
: PollBuffer()
{}

int32_t CAN::CANOpenBuffer::fromCANBuffer(CAN::CANBuffer * other)
{
	pdo_id = (other->cob_id & 0x0780) >> 7;
	node_id = other->cob_id & 0x7F;

	uint8_t data[8];
	int32_t len = other->read(data, 8);
	return write(data, len);
}

int32_t CAN::CANOpenBuffer::toCANBuffer(CAN::CANBuffer * buffer)
{
	buffer->cob_id = ((pdo_id & 0xF) << 7) | (node_id & 0x7F);
	
	uint8_t data[8];
	int32_t len = read(data, 8);
	return buffer->write(data, len);
}
