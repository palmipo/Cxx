#ifndef SOCKET_TCP_FIFO_H
#define SOCKET_TCP_FIFO_H

#include "sockettcp.h"
#include <queue>

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
	class SocketBuffer;
	class SOCKET_DLL SocketTcpFifo : public SocketTcp
	{
		public:
			SocketTcpFifo();

			virtual int32_t read(uint8_t *, int32_t);
			virtual int32_t actionIn();
		
		protected:
			std::queue < SocketBuffer > _fifo;
	};
}

#endif /* SOCKET_TCP_FIFO_H */
