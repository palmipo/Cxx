#include "canbus.h"
#include "canexception.h"
#include "canbuffer.h"
#include "polldevice.h"

CAN::Bus::Bus(PollDevice * device)
: Device(device->handler())
, _device(device)
{}

int32_t CAN::Bus::writeData(CAN::CANBuffer * buffer)
{
	uint8_t data[8];
	memset(data, 0, 8);
	int32_t len = buffer->read(data, 8);
	return writeData(buffer->cob_id, data, len);
}

int32_t CAN::Bus::readData(CAN::CANBuffer * buffer)
{
	uint8_t data[8];
	memset(data, 0, 8);
	int32_t len = readData(&(buffer->cob_id), data, 8);
	buffer->write(data, len);

	return len;
}
