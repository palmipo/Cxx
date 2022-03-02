#include "socketbase.h"
#include "socketexception.h"
#include "sys/types.h"
#include "sys/socket.h"

/* constructeur socket client */
Socket::SocketBase::SocketBase()
: PollDevice(Device::SOCKET)
, _srv_mode(0)
{}

/* constructeur socket serveur */
Socket::SocketBase::SocketBase(const std::string & addr, int16_t port)
: PollDevice(Device::SOCKET)
, _srv_mode(1)
{}

Socket::SocketBase::~SocketBase()
{
}

int32_t Socket::SocketBase::isServerMode() const
{
    return _srv_mode;
}

void Socket::SocketBase::setReuseAddr(int32_t reuseEnable)
{
	if (::setsockopt(_handler, SOL_SOCKET, SO_REUSEADDR, &reuseEnable, sizeof(reuseEnable)) == -1)
	{
		throw SocketException(__FILE__, __LINE__,errno);
	}
}

void Socket::SocketBase::setBroadcast(int32_t broadcastEnable)
{
	if (::setsockopt(_handler, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable)) == -1)
	{
		throw SocketException(__FILE__, __LINE__,errno);
	}
}

void Socket::SocketBase::setBufferSize(int32_t buf_size)
{
    if (setsockopt(_handler, SOL_SOCKET, SO_RCVBUF, (void *)&buf_size, sizeof(buf_size)) < 0)
    {
       throw SocketException(__FILE__, __LINE__, errno);
    }

    if (setsockopt (_handler, SOL_SOCKET, SO_SNDBUF, (void *)&buf_size, sizeof(buf_size)) < 0)
    {
        throw SocketException(__FILE__, __LINE__, errno);
    }
}

void Socket::SocketBase::setInterCharacterTimer(int32_t timeout)
{
    struct timeval sttimeout;      
    sttimeout.tv_sec = timeout;
    sttimeout.tv_usec = 0;

    if (setsockopt(_handler, SOL_SOCKET, SO_RCVTIMEO, (void *)&sttimeout, sizeof(sttimeout)) < 0)
    {
        throw SocketException(__FILE__, __LINE__, errno);
    }

    if (setsockopt (_handler, SOL_SOCKET, SO_SNDTIMEO, (void *)&sttimeout, sizeof(sttimeout)) < 0)
    {
        throw SocketException(__FILE__, __LINE__, errno);
    }
}

int32_t Socket::SocketBase::getInterCharacterTimer()
{
	socklen_t sttimeout_length;
    struct timeval sttimeout;      
    sttimeout.tv_sec = 0;
    sttimeout.tv_usec = 0;

    if (getsockopt(_handler, SOL_SOCKET, SO_RCVTIMEO, (void *)&sttimeout, &sttimeout_length) < 0)
    {
        throw SocketException(__FILE__, __LINE__, errno);
    }
	
	return sttimeout.tv_sec;
}

