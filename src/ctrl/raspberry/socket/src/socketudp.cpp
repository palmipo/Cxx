#include "socketudp.h"
#include "socketexception.h"
#include "sys/types.h"
#include "sys/socket.h"
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <iostream>

/* constructeur socket client */
Socket::SocketUdp::SocketUdp()
: Socket::SocketBase()
{
	if ((_handler = ::socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		throw SocketException(__FILE__, __LINE__,errno);
	}
}

/* constructeur socket listen */
Socket::SocketUdp::SocketUdp(const std::string & addr, int16_t port)
: Socket::SocketBase(addr, port)
{
	if ((_handler = ::socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		throw SocketException(__FILE__, __LINE__,errno);
	}

	::memset(&_st_sockaddr_in, 0, sizeof(struct sockaddr_in));

	_st_sockaddr_in.sin_family = AF_INET;
	_st_sockaddr_in.sin_port = ::htons(port);
	if (::inet_aton(addr.c_str(), &_st_sockaddr_in.sin_addr) != 1)
	{
		throw SocketException(__FILE__, __LINE__,errno);
	}

	if (::bind(_handler, (struct sockaddr *) &_st_sockaddr_in, sizeof(struct sockaddr_in)) < 0)
	{
		throw SocketException(__FILE__, __LINE__,errno);
	}
}

Socket::SocketUdp::~SocketUdp()
{
	::shutdown(_handler, SHUT_RDWR);
	::close(_handler);
}

void Socket::SocketUdp::broadcast(int16_t port)
{
	Socket::SocketUdp::setBroadcast(1);

	memset(&_st_sockaddr_in, 0, sizeof(struct sockaddr_in));
	_st_sockaddr_in.sin_family = AF_INET;
	_st_sockaddr_in.sin_port = ::htons(port);
	_st_sockaddr_in.sin_addr.s_addr = htonl(INADDR_BROADCAST);

	if (::bind(_handler, (struct sockaddr *) &_st_sockaddr_in, sizeof(struct sockaddr_in)) < 0)
	{
		throw SocketException(__FILE__, __LINE__,errno);
	}
}

void Socket::SocketUdp::connexion(const std::string & addr, int16_t port)
{
	memset(&_st_sockaddr_in, 0, sizeof(struct sockaddr_in));

	_st_sockaddr_in.sin_family = AF_INET;
	_st_sockaddr_in.sin_port = ::htons(port);
	if (::inet_aton(addr.c_str(), &_st_sockaddr_in.sin_addr) != 1)
	{
		throw SocketException(__FILE__, __LINE__,errno);
	}
}

int32_t Socket::SocketUdp::write(uint8_t * msg, int32_t length)
{
	int32_t len = ::sendto(_handler, msg, length, 0, (const struct sockaddr *) &_st_sockaddr_in, (socklen_t) sizeof(struct sockaddr_in));
	if (len < 0)
	{
		throw SocketException(__FILE__, __LINE__,errno);
	}

	return len;
}

int32_t Socket::SocketUdp::read(uint8_t * msg, int32_t length)
{
	socklen_t st_sockaddr_in_len;
	struct sockaddr st_sockaddr_in;
	int32_t len = ::recvfrom(_handler, msg, length, 0, &st_sockaddr_in, &st_sockaddr_in_len);
	if (len < 0)
	{
		throw SocketException(__FILE__, __LINE__,errno);
	}

	return len;
}

