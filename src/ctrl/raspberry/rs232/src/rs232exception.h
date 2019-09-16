#ifndef RS232_EXCEPTION_H
#define RS232_EXCEPTION_H

#include "pollexception.h"

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_RS232_DLL
#define RS232_DLL __declspec(dllexport)
#else
#define RS232_DLL __declspec(dllimport)
#endif
#else
#define RS232_DLL
#endif

class RS232_DLL RS232Exception : public PollException
{
    public:
        RS232Exception(const std::string & fichier, int32_t ligne, int32_t numerror, PollDevice * device = 0)
		: PollException(fichier, ligne, numerror, device)
		{}

        RS232Exception(const std::string & fichier, int32_t ligne, const std::string & error, PollDevice * device = 0)
		: PollException(fichier, ligne, error, device)
		{}
};

#endif /* RS232_EXCEPTION_H */
