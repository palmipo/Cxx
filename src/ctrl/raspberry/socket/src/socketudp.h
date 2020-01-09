#ifndef SOCKETUDP_H
#define SOCKETUDP_H

#include "socketbase.h"
#include <arpa/inet.h>

namespace Socket
{
	class SocketUdp : public SocketBase
	{
	public:
		SocketUdp();
		SocketUdp(const std::string &, int16_t);
		virtual ~SocketUdp();

		virtual void connexion(const std::string &, int16_t);
		virtual void broadcast(int32_t);

		virtual int32_t write(uint8_t *, int32_t);
		virtual int32_t read(uint8_t *, int32_t);

	protected:
		struct sockaddr_in _st_sockaddr_in;
	};
}

#endif /* SOCKETUDP_H */
