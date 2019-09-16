#include "genericdevice.h"
#include "polldevice.h"
#include "pollbuffer.h"
#include "pollexception.h"
#include <thread>

GenericDevice::GenericDevice(PollDevice * device)
: TowerDevice(device)
{}

int32_t GenericDevice::read(uint8_t * data, int32_t length, int32_t max_retry, int32_t timeout)
{
	int32_t retry = 0;
	while (_fifo.empty() && (retry < max_retry))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
		retry += 1;
	}
	
	if (_fifo.empty())
	{
		throw PollException(__FILE__, __LINE__, "fifo vide");
	}

	PollBuffer * buffer = _fifo.front();
	_fifo.pop();
	
	int32_t len = buffer->read(data, length);
	delete buffer;

	return len;
}

int32_t GenericDevice::write(uint8_t * data, int32_t length)
{
	return _device->write(data, length);
}

int32_t GenericDevice::actionIn(uint8_t * data, int32_t length)
{
	PollBuffer * buffer = new PollBuffer();
	int32_t len = buffer->write(data, length);
	_fifo.push(buffer);
	return len;
}

int32_t GenericDevice::actionOut(uint8_t * data, int32_t length)
{
	return 0;
}

int32_t GenericDevice::actionError(uint8_t * data, int32_t length)
{
	return 0;
}
