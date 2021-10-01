#ifndef SOCKETBASE_H
#define SOCKETBASE_H

#include "polldevice.h"
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
	class SOCKET_DLL SocketBase : public PollDevice
	{
		public:
			SocketBase();
			SocketBase(const std::string &, int16_t);
			virtual ~SocketBase();

			virtual int32_t isServerMode() const;

			virtual void connexion(const std::string &, int16_t) = 0;
			virtual int32_t write(uint8_t *, int32_t) = 0;
			virtual int32_t read(uint8_t *, int32_t) = 0;

		protected:
			int32_t _srv_mode;
	};
}

#endif /* SOCKETBASE_H */
