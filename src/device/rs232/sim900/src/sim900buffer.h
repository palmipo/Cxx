#ifndef SIM900_BUFFER_H
#define SIM900_BUFFER_H

#include "pollbuffer.h"

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_SIM900_DLL
#define SIM900_DLL __declspec(dllexport)
#else
#define SIM900_DLL __declspec(dllimport)
#endif
#else
#define SIM900_DLL
#endif

class SIM900_DLL Sim900Buffer : public PollBuffer
{
	public:
		Sim900Buffer();
};

#endif /* SIM900_BUFFER_H */
