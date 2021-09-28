#ifndef POLL_MUTEX_H
#define POLL_MUTEX_H

#include <mutex>

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_POLL_FACTORY_DLL
#define POLL_FACTORY_DLL __declspec(dllexport)
#else
#define POLL_FACTORY_DLL __declspec(dllimport)
#endif
#else
#define POLL_FACTORY_DLL
#endif

class POLL_FACTORY_DLL PollMutex
{
	std::mutex &m_;

	public:
		PollMutex(std::mutex & m);
		~PollMutex();
};

#endif /* POLL_MUTEX_H */
