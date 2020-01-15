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
	Log::getLogger()->debug(__FILE__, __LINE__, "read");

	int32_t retry = 0;
	while (_fifo_in.empty() && (retry < max_retry))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
		retry += 1;
	}
	
	if (_fifo_in.empty())
	{
		throw RS232Exception(__FILE__, __LINE__, "fifo vide !");
	}

	RS232Buffer * buffer = _fifo_in.front();
	_fifo_in.pop();

	int32_t len = buffer->read(msg, length);
	delete buffer;

	return len;
}

int32_t RS232Fifo::write(uint8_t * msg, int32_t length)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "write");

	RS232Buffer * buffer = new RS232Buffer;
	int32_t len = buffer->write(msg, length);
	_fifo_out.push(buffer);
	
	return len;
}

int32_t RS232Fifo::actionIn()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	uint8_t msg[512];
	int32_t len = RS232::recvUntilEnd(msg, 512);

	RS232Buffer * buffer = new RS232Buffer();
	buffer->write(msg, len);
	_fifo_in.push(buffer);

	return len;
}

int32_t RS232Fifo::actionOut()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionOut");

	// if (_fifo_out.empty())
	// {
		// throw Socket::SocketException(__FILE__, __LINE__, "fifo vide !");
	// }

	if (!_fifo_out.empty())
	{
		RS232Buffer * buffer = _fifo_out.front();
		_fifo_out.pop();

		uint8_t msg[512];
		int32_t length = buffer->read(msg, 512);
		int32_t len = RS232::write(msg, length);
		delete buffer;

		return len;
	}
	
	return 0;
}
