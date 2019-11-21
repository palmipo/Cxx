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
		std::cerr << __FILE__ << __LINE__ << std::endl;
		throw SocketException(errno);
	}
}

/* constructeur socket listen */
Socket::SocketUdp::SocketUdp(const std::string & addr, s16 port)
: Socket::SocketBase(addr, port)
{
	if ((_handler = ::socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		std::cerr << __FILE__ << __LINE__ << std::endl;
		throw SocketException(errno);
	}

	::memset(&_st_sockaddr_in, 0, sizeof(struct sockaddr_in));

	_st_sockaddr_in.sin_family = AF_INET;
	_st_sockaddr_in.sin_port = ::htons(port);
	if (::inet_aton(addr.c_str(), &_st_sockaddr_in.sin_addr) != 1)
	{
		std::cerr << __FILE__ << __LINE__ << std::endl;
		throw SocketException(errno);
	}

	if (::bind(_handler, (struct sockaddr *) &_st_sockaddr_in, sizeof(struct sockaddr_in)) < 0)
	{
		std::cerr << __FILE__ << __LINE__ << std::endl;
		throw SocketException(errno);
	}
}

Socket::SocketUdp::~SocketUdp()
{
	::shutdown(_handler, SHUT_RDWR);
	::close(_handler);
}

void Socket::SocketUdp::connexion(const std::string & addr, s16 port)
{
	memset(&_st_sockaddr_in, 0, sizeof(struct sockaddr_in));

	_st_sockaddr_in.sin_family = AF_INET;
	_st_sockaddr_in.sin_port = ::htons(port);
	if (::inet_aton(addr.c_str(), &_st_sockaddr_in.sin_addr) != 1)
	{
		std::cerr << __FILE__ << __LINE__ << std::endl;
		throw SocketException(errno);
	}
}

s32 Socket::SocketUdp::write(u8 * msg, s32 length)
{

	s32 len = ::sendto(_handler, msg, length, 0, (const struct sockaddr *) &_st_sockaddr_in, (socklen_t) sizeof(struct sockaddr_in));
	if (len < 0)
	{
		std::cerr << __FILE__ << __LINE__ << std::endl;
		throw SocketException(errno);
	}

	return len;
}

s32 Socket::SocketUdp::read(u8 * msg, s32 length)
{
	socklen_t st_sockaddr_in_len;
	struct sockaddr st_sockaddr_in;
	s32 len = ::recvfrom(_handler, msg, length, 0, &st_sockaddr_in, &st_sockaddr_in_len);
	if (len < 0)
	{
		std::cerr << __FILE__ << __LINE__ << std::endl;
		throw SocketException(errno);
	}

	return len;
}
