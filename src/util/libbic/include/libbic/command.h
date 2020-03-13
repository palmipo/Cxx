#ifndef BIC_COMMAND_H
#define BIC_COMMAND_H

#include <string>
#include <map>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <exception>

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_BIC_DLL
#define BIC_DLL __declspec(dllexport)
#else
#define BIC_DLL __declspec(dllimport)
#endif
#else
#define BIC_DLL
#endif

namespace BIC
{
	class BIC_DLL Command
	{
		public:
			Command(const std::string &);
			virtual ~Command();

			std::string str_protocol;
			virtual void xml_read(xmlNode *) = 0;
	};
}

#endif
