#ifndef RS232FACTORY_H
#define RS232FACTORY_H

#include "pollfactory.h"
#include <string>
#include <map>
#include <list>
#include <poll.h>
#include <termios.h>

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_RS232_DLL
#define RS232_DLL __declspec(dllexport)
#else
#define RS232_DLL __declspec(dllimport)
#endif
#else
#define RS232_DLL
#endif

class RS232;
class RS232Fifo;
class RS232_DLL RS232Factory : public PollFactory
{
    public:
        RS232Factory();
        virtual ~RS232Factory();
        
        virtual RS232 * add(const std::string &);
        virtual RS232Fifo * addFifo(const std::string &);
        virtual RS232 * get(const std::string &);
        virtual void del(const std::string &);

	protected:
        virtual int32_t actionIn(PollDevice*) = 0;
        virtual int32_t actionOut(PollDevice*) = 0;
        virtual int32_t actionError(PollDevice*) = 0;
    
    protected:
        std::map<std::string, int32_t> _port;
        

};

#endif
