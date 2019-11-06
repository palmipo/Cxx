#include "pollfactory.h"
#include "polldevice.h"
#include "pollmutex.h"
#include "pollexception.h"
// #include "log.h"
#include <sstream>

PollFactory::PollFactory()
{}

PollFactory::~PollFactory()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "~PollFactory");

	std::map<int32_t, PollDevice*>::iterator it = _liste.begin();
	while (it != _liste.end())
	{
		delete it->second; it->second = 0;
		it++;
	}
}

void PollFactory::add(PollDevice * t)
{
	_liste[t->handler()] = t;
}

void PollFactory::del(int32_t id)
{
	PollMutex mutex(_mutex);

	std::map < int32_t, PollDevice * >::iterator it = _liste.find(id);
	if (it != _liste.end())
	{
        	if (it->second)
		{
			delete it->second;
			it->second = 0;
		}
		_liste.erase(it);
	}
	else
	{
		std::stringstream ss;
		ss << "handler inconnu : " << id;
		throw PollException(__FILE__, __LINE__, ss.str());
	}
}

PollDevice* PollFactory::get(int32_t id)
{
	std::map < int32_t, PollDevice * >::iterator it = _liste.find(id);
	if (it != _liste.end())
	{
		return it->second;
	}
	
	std::stringstream ss;
	ss << "handler inconnu : " << id;
	throw PollException(__FILE__, __LINE__, ss.str());
}

int32_t PollFactory::scrute(int32_t timeout, int32_t scruteIn, int32_t scruteOut, int32_t scruteError)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "scrute");

	int32_t cpt = 0;
	int32_t nb = _liste.size();
	struct pollfd * lst_fd = new struct pollfd[nb];
	{
		PollMutex mutex(_mutex);
		std::map<int32_t, PollDevice*>::iterator it = _liste.begin();
		while(it != _liste.end())
		{
			lst_fd[cpt].fd = it->second->handler();
			lst_fd[cpt].events = (scruteIn ? POLLIN | POLLPRI : 0) | (scruteOut ? POLLOUT | POLLWRBAND : 0) | (scruteError ? POLLERR | POLLHUP | POLLNVAL : 0);
			lst_fd[cpt].revents = 0;
			cpt += 1;
			it++;
		}
	}

	int32_t ret = poll(lst_fd, cpt, timeout);
	if (ret < 0)
	{
		throw PollException(__FILE__, __LINE__, errno);
	}

	else if (ret > 0)
	{
		for (int32_t i=0; i<cpt; ++i)
		{
			if (lst_fd[i].revents)
			{
				action(lst_fd[i]);
			}
		}
	}

	delete[] lst_fd;

	return ret;
}

int32_t PollFactory::action(const pollfd & evnt)
{
	std::map<int32_t, PollDevice*>::iterator it = _liste.find(evnt.fd);
	if (it == _liste.end())
	{
		std::stringstream ss;
		ss << "inconnu au bataillon !!!";
		throw PollException(__FILE__, __LINE__, ss.str());
	}

	else if (evnt.revents & (POLLERR | POLLHUP | POLLNVAL))
	{
		// {
		// std::stringstream ss;
		// ss << "POLLERR : " << (int)(evnt.revents & POLLERR);
		// ss << ", POLLHUP : " << (int)(evnt.revents & POLLHUP);
		// ss << ", POLLNVAL : " << (int)(evnt.revents & POLLNVAL) << std::endl;
		// Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		// }
		if (it->second)
		{
			return actionError(it->second);
		}
	}

	else if (evnt.revents & (POLLPRI | POLLIN))
	{
		// {
		// std::stringstream ss;
		// ss << "POLLPRI : " << (int)(evnt.revents & POLLPRI);
		// ss << ", POLLIN : " << (int)(evnt.revents & POLLIN) << std::endl;
		// Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		// }
		if (it->second)
		{
			return actionIn(it->second);
		}
	}

	else if (evnt.revents & (POLLOUT | POLLWRBAND))
	{
		// {
		// std::stringstream ss;
		// ss << "POLLOUT : " << (int)(evnt.revents & POLLOUT);
		// ss << ", POLLWRBAND : " << (int)(evnt.revents & POLLWRBAND) << std::endl;
		// Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		// }
		if (it->second)
		{
			return actionOut(it->second);
		}
	}

	std::stringstream ss;
	ss << "evnt non traite !!!";
	throw PollException(__FILE__, __LINE__, ss.str());
}
