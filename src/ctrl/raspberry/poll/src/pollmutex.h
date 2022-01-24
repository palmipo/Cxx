#ifndef POLL_MUTEX_H
#define POLL_MUTEX_H

#include <mutex>

class PollMutex
{
	std::mutex &m_;

	public:
		PollMutex(std::mutex & m);
		~PollMutex();
};

#endif /* POLL_MUTEX_H */
