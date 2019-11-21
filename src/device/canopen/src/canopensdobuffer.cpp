#include "canopensdobuffer.h"
#include <cstring>


CAN::CANOpenSdoBuffer::CANOpenSdoBuffer()
: PollBuffer()
{}

int32_t CAN::CANOpenSdoBuffer::fromCANOpenBuffer(CAN::CANOpenBuffer * other)
{
	pdo_id = other->pdo_id;
	node_id = other->node_id;

	int32_t cpt = 0;
	uint8_t data[8];
	memset(data, 0, 8);
	int32_t len = other->read(data, 8);

	if (cpt < len)
	{
		command = data[cpt]; cpt += 1;
	}
	if (cpt < len)
	{
		index = data[cpt]; cpt += 1;
	}
	if (cpt < len)
	{
		index |= (data[cpt] << 8); cpt += 1;
	}
	if (cpt < len)
	{
		subindex = data[cpt]; cpt += 1;
	}
	return write(data+cpt, len-cpt);
}

int32_t CAN::CANOpenSdoBuffer::toCANOpenBuffer(CAN::CANOpenBuffer * buffer)
{
	buffer->pdo_id = pdo_id;
	buffer->node_id = node_id;

	int32_t cpt = 0;
	uint8_t data[8];
	memset(data, 0, 8);
	data[cpt] = command; cpt += 1;
	data[cpt] = index & 0x00FF; cpt += 1;
	data[cpt] = (index & 0xFF00) >> 8; cpt += 1;
	data[cpt] = subindex; cpt += 1;
	cpt += read(data+cpt, 8-cpt);
	
	return buffer->write(data, 8);
}
