#ifndef BIC_SIGNAL_H
#define BIC_SIGNAL_H

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
	class Index;
	class BIC_DLL Signal
	{
		public:
			Index * find_index(const std::string &);

			std::string str_signal_id;
			void xml_read(xmlNode *);

		protected:
			std::map < std::string, Index * > map_signaux;

	};
}

#endif
