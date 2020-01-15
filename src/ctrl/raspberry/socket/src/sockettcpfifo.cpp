#include "sockettcpfifo.h"
#include "socketexception.h"
#include "socketbuffer.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <thread>
#include <iomanip>

/* constructeur socket client */
Socket::SocketTcpFifo::SocketTcpFifo()
: Socket::SocketTcp()
{}

int32_t Socket::SocketTcpFifo::read(uint8_t * msg, int32_t length)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "read");

	int32_t retry = 0;
	while (_fifo_in.empty() && (retry < _max_retry))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(_timeout));
		retry += 1;
	}
	
	if (_fifo_in.empty())
	{
		throw Socket::SocketException(__FILE__, __LINE__, "fifo vide !");
	}

	int32_t len = 0;
	SocketBuffer buffer = _fifo_in.front();
	_fifo_in.pop();

	len = buffer.read(msg, length);

	return len;
}

int32_t Socket::SocketTcpFifo::write(uint8_t * msg, int32_t length)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "write");

	SocketBuffer buffer;
	int32_t len = buffer.write(msg, length);
	_fifo_out.push(buffer);
	
	return len;
}

int32_t Socket::SocketTcpFifo::actionOut()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionOut");

	if (_fifo_out.empty())
	{
		throw Socket::SocketException(__FILE__, __LINE__, "fifo vide !");
	}

	SocketBuffer buffer = _fifo_out.front();
	_fifo_out.pop();

	uint8_t msg[512];
	int32_t length = buffer.read(msg, 512);
    int32_t len = Socket::SocketTcp::write(msg, length);

    return len;
}

int32_t Socket::SocketTcpFifo::actionIn()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	uint8_t msg[512];
	int32_t len = Socket::SocketTcp::read(msg, 512);

	SocketBuffer buffer;
	buffer.write(msg, len);
	_fifo_in.push(buffer);
	
	return len;
}
