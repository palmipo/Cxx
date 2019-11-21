#ifndef RS232_BUFFER_H
#define RS232_BUFFER_H

#include "pollbuffer.h"

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_RS232_DLL
#define RS232_DLL __declspec(dllexport)
#else
#define RS232_DLL __declspec(dllimport)
#endif
#else
#define RS232_DLL
#endif

class RS232_DLL RS232Buffer : public PollBuffer
{
	public:
		RS232Buffer();
};

#endif /* RS232_BUFFER_H */
