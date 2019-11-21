#ifndef SOCKET_BUFFER_H
#define SOCKET_BUFFER_H

#include "pollbuffer.h"

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
	class SOCKET_DLL SocketBuffer : public PollBuffer
	{
		public:
			SocketBuffer();
	};
}

#endif /* SOCKET_BUFFER_H */
