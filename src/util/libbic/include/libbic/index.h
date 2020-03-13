#ifndef BIC_INDEX_H
#define BIC_INDEX_H

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
	class Command;
	class BIC_DLL Index
	{
		public:
			Command * find_cmd(const std::string &);

			std::string str_id;
			void xml_read(xmlNode *);
			
		protected:
			std::map < std::string, Command * > map_cmd;

	};
}

#endif
