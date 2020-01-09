#ifndef SOCKET_TCP_H
#define SOCKET_TCP_H

#include "socketbase.h"

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
	class SOCKET_DLL SocketTcp : public SocketBase
	{
		public:
			SocketTcp();
			SocketTcp(int32_t);
			SocketTcp(const std::string &, int16_t);
			virtual ~SocketTcp();

			virtual void connexion(const std::string &, int16_t);
			virtual void setInterCharacterTimer(int32_t);
			virtual int32_t getInterCharacterTimer();
			virtual void setBufferSize(int32_t);

			virtual int32_t write(uint8_t *, int32_t);
			virtual int32_t read(uint8_t *, int32_t);
	};
}

#endif /* SOCKETTCP_H */
