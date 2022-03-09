#ifndef MUTEX_H
#define MUTEX_H

#include <mutex>
#include <thread>

class Mutex
{
	std::mutex &m_;

	public:
Mutex(std::mutex & m)
: m_(m)
{
	m_.lock();
}

~Mutex()
{
	m_.unlock();
}

};

#endif /* MUTEX_H */
