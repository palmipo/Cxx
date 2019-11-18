#ifndef SOCKET_CAN_H
#define SOCKET_CAN_H

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_SOCKET_DLL
#define SOCKET_DLL __declspec(dllexport)
#else
#define SOCKET_DLL __declspec(dllimport)
#endif
#else
#define SOCKET_DLL
#endif

#include "polldevice.h"
#include <string>

namespace Socket
{
	class SOCKET_DLL SocketCan : public PollDevice
	{
		public:
			SocketCan();
			virtual ~SocketCan();

			virtual void connexion(const std::string &);
			virtual int32_t write(uint8_t *, int32_t);
			virtual int32_t read(uint8_t *, int32_t);

			virtual int32_t actionIn();
			virtual int32_t actionOut();
			virtual int32_t actionError();
	};
}

#endif /* SOCKET_CAN_H */
