#ifndef BIC_CTRLCONFIGBASE_H
#define BIC_CTRLCONFIGBASE_H

#include <string>
#include <libxml/parser.h>
#include <libxml/tree.h>

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
	class BIC_DLL CtrlConfigBase
	{
		public:
			CtrlConfigBase(const std::string &);
		
			std::string str_iface;
			virtual void xml_read(xmlNode *) = 0;
	};
}

#endif
