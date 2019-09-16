#include "pollbuffer.h"
#include "log.h"
#include <sstream>

/* constructeur socket client */
PollBuffer::PollBuffer()
{}

int32_t PollBuffer::read(uint8_t * msg, int32_t length)
{
	// std::stringstream ss;
	// ss << "read() : " << _buffer.size() << " " << length;
	// Log::getLogger()->DEBUG(__FILE__, __LINE__, ss.str());

	int32_t len = (_buffer.size() > length) ? length : _buffer.size();
	for (int32_t i=0; i<len; ++i)
	{
		msg[i] = _buffer[i];
	}
	return len;
}

int32_t PollBuffer::write(uint8_t * msg, int32_t length)
{
	_buffer.resize(length);
	for (int32_t i=0; i<length; ++i)
	{
		_buffer[i] = msg[i];
	}

	// std::stringstream ss;
	// ss << "write() : " << _buffer.size() << " " << length;
	// Log::getLogger()->DEBUG(__FILE__, __LINE__, ss.str());

	return length;
}
