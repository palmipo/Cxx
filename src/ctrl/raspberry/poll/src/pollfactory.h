#ifndef POLL_FACTORY_H
#define POLL_FACTORY_H

#include <cstdint>
#include <map>
#include <list>
#include <poll.h>
#include <mutex>

#ifdef  __CYGWIN__
#ifdef MAKE_POLL_FACTORY_DLL
#define POLL_FACTORY_DLL __declspec(dllexport)
#else
#define POLL_FACTORY_DLL __declspec(dllimport)
#endif
#else
#define POLL_FACTORY_DLL
#endif

class PollDevice;
class POLL_FACTORY_DLL PollFactory
{
	public:
		PollFactory();
		virtual ~PollFactory();
		
		virtual void add(PollDevice*);
		virtual PollDevice* get(int32_t);
		virtual void del(int32_t);

		//!\ sous windows POLLOUT gene le POLLIN
		virtual int32_t scrute(int32_t, int32_t=1, int32_t=0, int32_t=1);

		virtual void setActionInCallback(int32_t (*)(PollDevice*));
		virtual void setActionOutCallback(int32_t (*)(PollDevice*));
		virtual void setActionErrorCallback(int32_t (*)(PollDevice*));

		virtual int32_t actionIn(PollDevice*);
		virtual int32_t actionOut(PollDevice*);
		virtual int32_t actionError(PollDevice*);

	protected:
		virtual int32_t action(const pollfd &);
		std::map<int32_t, PollDevice*> _liste;
		std::mutex _mutex;

		int32_t (*_clb_in)(PollDevice*);
		int32_t (*_clb_out)(PollDevice*);
		int32_t (*_clb_error)(PollDevice*);
};

#endif
