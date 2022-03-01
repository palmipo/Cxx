#ifndef RS232FACTORY_H
#define RS232FACTORY_H

#include <string>
#include <map>
#include <list>
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
class RS232_DLL RS232Factory
{
	public:
		RS232Factory();
		virtual ~RS232Factory();

		virtual RS232 * add(const std::string &);
		virtual RS232 * get(const std::string &);
		virtual void del(const std::string &);

	protected:
		std::map<std::string, int32_t> _port;
};

#endif
