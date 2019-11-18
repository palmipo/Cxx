#include "pollmutex.h"
#include <thread>

PollMutex::PollMutex(std::mutex & m)
: m_(m)
{
	m_.lock();
}

PollMutex::~PollMutex()
{
	m_.unlock();
}
