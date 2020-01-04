#ifndef SIM900_EXCEPTION_H
#define SIM900_EXCEPTION_H

#include "pollexception.h"

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_SIM900_DLL
#define SIM900_DLL __declspec(dllexport)
#else
#define SIM900_DLL __declspec(dllimport)
#endif
#else
#define SIM900_DLL
#endif

class SIM900_DLL Sim900Exception : public PollException
{
    public:
        Sim900Exception(const std::string & fichier, int32_t ligne, int32_t numerror, PollDevice * device = 0)
		: PollException(fichier, ligne, numerror, device)
		{}

        Sim900Exception(const std::string & fichier, int32_t ligne, const std::string & error, PollDevice * device = 0)
		: PollException(fichier, ligne, error, device)
		{}
};

#endif /* SIM900_EXCEPTION_H */
