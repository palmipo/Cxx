#ifndef GPIO_EXCEPTION_H
#define GPIO_EXCEPTION_H

#include "pollexception.h"

#if defined __MINGW64__ || __MINGW32__ || defined __CYGWIN__
#ifdef MAKE_GPIO_DLL
#define GPIO_DLL __declspec(dllexport)
#else
#define GPIO_DLL __declspec(dllimport)
#endif
#else
#define GPIO_DLL
#endif

class GPIO_DLL GpioException : public PollException
{
    public:
        GpioException(const std::string & fichier, int32_t ligne, int32_t numerror, PollDevice * device = 0)
		: PollException(fichier, ligne, numerror, device)
		{}

        GpioException(const std::string & fichier, int32_t ligne, const std::string & error, PollDevice * device = 0)
		: PollException(fichier, ligne, error, device)
		{}
};

#endif /* GPIO_EXCEPTION_H */
