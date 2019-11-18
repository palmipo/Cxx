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
		SocketUdp(const std::string &, s16);
		virtual ~SocketUdp();

		virtual void connexion(const std::string &, s16);
		virtual s32 write(u8 *, s32);
		virtual s32 read(u8 *, s32);
	
	protected:
		struct sockaddr_in _st_sockaddr_in;
	};
}

#endif /* SOCKETUDP_H */
