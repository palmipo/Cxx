#include "rs232fifo.h"
#include "rs232exception.h"
#include "log.h"
#include <thread>
#include <sstream>
#include <iomanip>

RS232Fifo::RS232Fifo(const std::string & device_p)
: RS232(device_p)
{}

RS232Fifo::~RS232Fifo()
{}

int32_t RS232Fifo::read(uint8_t * msg, int32_t length, int32_t max_retry, int32_t timeout)
{
	int32_t retry = 0;
	while (_fifo.empty() && (retry < max_retry))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
		retry += 1;
	}
	
	if (_fifo.empty())
	{
		throw RS232Exception(__FILE__, __LINE__, "fifo vide !");
	}

	int32_t len = 0;
	RS232Buffer * buffer = _fifo.front();
	_fifo.pop();

	len = buffer->read(msg, length);
	delete buffer;

	return len;
}

int32_t RS232Fifo::actionIn()
{
	uint8_t msg[512];
	int32_t len = RS232::recvUntilEnd(msg, 512);

	RS232Buffer * buffer = new RS232Buffer();
	buffer->write((uint8_t*)msg, len);
	_fifo.push(buffer);

	return len;
}
