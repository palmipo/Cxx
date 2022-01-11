#ifndef SOCKETFACTORY_H
#define SOCKETFACTORY_H

#include "pollfactory.h"
#include <map>
//~ #include <list>
//~ #include <poll.h>
#include <string>

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_SOCKET_DLL
#define SOCKET_DLL __declspec(dllexport)
#else
#define SOCKET_DLL __declspec(dllimport)
#endif
#else
#define SOCKET_DLL
#endif

namespace Socket
{
	class SocketBase;
	class SocketUdp;
	class SocketTcp;
	class SOCKET_DLL SocketFactory : public PollFactory
	{
		public:
			SocketFactory();
			virtual ~SocketFactory();

			virtual SocketTcp * addTcpServer(const std::string &, uint16_t);
			virtual SocketTcp * addTcpConnection(const std::string &, uint16_t);

			virtual SocketUdp * addUdpConnection(const std::string &, uint16_t);

			virtual SocketBase * get(const std::string &, uint16_t);
			virtual void del(const std::string &, uint16_t);

			/* ip:port => handler */
			std::map < std::pair < std::string, uint16_t > , int32_t > _hosts;
	};
}

#endif /* TCPSOCKET_H */
