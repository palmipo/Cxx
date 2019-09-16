#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

#include "pollexception.h"

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
	class SOCKET_DLL SocketException : public PollException
	{
	public:
		SocketException(const std::string & fichier, int32_t ligne, int32_t numerror, PollDevice * device = 0)
		: PollException(fichier, ligne, numerror, device)
		{}

		SocketException(const std::string & fichier, int32_t ligne, const std::string & err, PollDevice * device = 0)
		: PollException(fichier, ligne, err, device)
		{}
	};
}

#endif /* SOCKETEXCEPTION_H */
