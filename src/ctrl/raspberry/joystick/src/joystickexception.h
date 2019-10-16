#ifndef JOYSTICK_EXCEPTION_H
#define JOYSTICK_EXCEPTION_H

#include "pollexception.h"

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_JOYSTICK_DLL
#define JOYSTICK_DLL __declspec(dllexport)
#else
#define JOYSTICK_DLL __declspec(dllimport)
#endif
#else
#define JOYSTICK_DLL
#endif

class JOYSTICK_DLL JoystickException : public PollException
{
    public:
        JoystickException(const std::string & fichier, int32_t ligne, int32_t numerror, PollDevice * device = 0)
		: PollException(fichier, ligne, numerror, device)
		{}

        JoystickException(const std::string & fichier, int32_t ligne, const std::string & error, PollDevice * device = 0)
		: PollException(fichier, ligne, error, device)
		{}
};

#endif /* JOYSTICK_EXCEPTION_H */
