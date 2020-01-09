#ifndef SOCKETFACTORY_H
#define SOCKETFACTORY_H

#include "pollfactory.h"
#include <map>
#include <list>
#include <poll.h>
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
	class SocketTcp;
	class SocketTcpFifo;
	class SOCKET_DLL SocketFactory : public PollFactory
	{
		public:
			SocketFactory();
			virtual ~SocketFactory();

			virtual SocketTcp * addTcpServer(const std::string &, uint16_t);
			virtual SocketTcp * addTcpConnection(const std::string &, uint16_t);
			virtual SocketTcpFifo * addTcpFifoConnection(const std::string &, uint16_t);

			virtual SocketTcp * getTcp(const std::string &, uint16_t);
			virtual void delTcp(const std::string &, uint16_t);

		protected:
			virtual int32_t actionIn(PollDevice*) = 0;
			virtual int32_t actionOut(PollDevice*) = 0;
			virtual int32_t actionError(PollDevice*) = 0;

			/* ip:port => handler */
			std::map < std::pair < std::string, uint16_t > , int32_t > _hosts;
	};
}

#endif /* TCPSOCKET_H */
