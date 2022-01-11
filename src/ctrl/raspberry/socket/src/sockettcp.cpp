#include "sockettcp.h"
#include "socketexception.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "log.h"
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <cerrno>
#include <unistd.h>
#include <sstream>
#include <iomanip>
#include <thread>

/* constructeur socket client */
Socket::SocketTcp::SocketTcp()
: Socket::SocketBase()
{
 	// Log::getLogger()->debug(__FILE__, __LINE__, "Socket::SocketTcp::SocketTcp");
}

/* constructeur socket accept */
Socket::SocketTcp::SocketTcp(int32_t hdl)
: Socket::SocketBase()
{
	// Log::getLogger()->debug(__FILE__, __LINE__, "Socket::SocketTcp::SocketTcp");

	socklen_t st_sockaddr_in_len = sizeof(struct sockaddr_in);
	struct sockaddr_in st_sockaddr_in;
	::memset(&st_sockaddr_in, 0, st_sockaddr_in_len);
	if ((_handler = ::accept(hdl, (struct sockaddr *) &st_sockaddr_in, &st_sockaddr_in_len)) < 0)
	{
		throw SocketException(__FILE__, __LINE__, errno);
	}

	setReuseAddr(1);
}

/* constructeur socket listen */
Socket::SocketTcp::SocketTcp(const std::string & addr, int16_t port)
: Socket::SocketBase(addr, port)
{
	// Log::getLogger()->debug(__FILE__, __LINE__, "Socket::SocketTcp::SocketTcp");

	if ((_handler = ::socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		throw SocketException(__FILE__, __LINE__, errno);
	}

	socklen_t st_sockaddr_in_len = sizeof(struct sockaddr_in);
	struct sockaddr_in st_sockaddr_in;
	::memset(&st_sockaddr_in, 0, st_sockaddr_in_len);

	st_sockaddr_in.sin_family = AF_INET;
	st_sockaddr_in.sin_port = ::htons(port);
	if (::inet_aton(addr.c_str(), &st_sockaddr_in.sin_addr) != 1)
	{
		throw SocketException(__FILE__, __LINE__, errno);
	}

	setReuseAddr(1);

	if (::bind(_handler, (struct sockaddr *) &st_sockaddr_in, st_sockaddr_in_len) < 0)
	{
		throw SocketException(__FILE__, __LINE__, errno);
	}

	if (::listen(_handler, 7) < 0)
	{
		throw SocketException(__FILE__, __LINE__, errno);
	}
}

Socket::SocketTcp::~SocketTcp()
{
	::shutdown(_handler, SHUT_RDWR);
	::close(_handler);
}

void Socket::SocketTcp::connexion(const std::string & addr, int16_t port)
{
	if (!isServerMode())
	{
		if ((_handler = ::socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			throw SocketException(__FILE__, __LINE__, errno);
		}

		setReuseAddr(1);

		socklen_t st_sockaddr_in_len = sizeof(struct sockaddr_in);
		struct sockaddr_in st_sockaddr_in;
		memset(&st_sockaddr_in, 0, st_sockaddr_in_len);

		st_sockaddr_in.sin_family = AF_INET;
		st_sockaddr_in.sin_port = ::htons(port);
		if (::inet_aton(addr.c_str(), &st_sockaddr_in.sin_addr) != 1)
		{
			throw SocketException(__FILE__, __LINE__, errno);
		}

		int32_t retry = 0;
		int32_t resultat = ::connect(_handler, (struct sockaddr *) &st_sockaddr_in, st_sockaddr_in_len);
		while ((resultat < 0) && (retry < _max_retry))
		{
			// /* tempo */
			std::this_thread::sleep_for(std::chrono::milliseconds(_timeout));

			// /* connexion */
			resultat = ::connect(_handler, (struct sockaddr *) &st_sockaddr_in, st_sockaddr_in_len);
			retry += 1;
		}

		if (resultat < 0)
		{
			throw SocketException(__FILE__, __LINE__, errno);
		}
	}
}

int32_t Socket::SocketTcp::write(uint8_t * msg, int32_t length)
{
	std::stringstream ss;
	ss << "socket out (" << length << ") :" << std::hex;
	for (int32_t i=0; i<length; ++i)
	{
		ss << " " << std::setfill('0') << std::setw(2) << (int)msg[i];
	}
	ss << std::dec << std::endl;
	Log::getLogger()->info(__FILE__, __LINE__, ss.str());

	int32_t len = ::send(_handler, msg, length, 0);
	if (len < 0)
	{
		throw SocketException(__FILE__, __LINE__, errno, this);
	}

	return len;
}

int32_t Socket::SocketTcp::read(uint8_t * msg, int32_t length)
{
	int32_t len = ::recv(_handler, msg, length, 0);
	if (len <= 0)
	{
		throw SocketException(__FILE__, __LINE__, errno, this);
	}

	std::stringstream ss;
	ss << "socket in (" << len << ") :" << std::hex;
	for (int32_t i=0; i<len; ++i)
	{
		ss << " " << std::setfill('0') << std::setw(2) << (int)msg[i];
	}
	ss << std::dec << std::endl;
	Log::getLogger()->info(__FILE__, __LINE__, ss.str());

	return len;
}
