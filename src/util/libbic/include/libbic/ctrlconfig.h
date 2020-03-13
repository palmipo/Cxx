#ifndef BIC_CTRLCONFIG_H
#define BIC_CTRLCONFIG_H

#include <string>
#include <map>
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
	class CtrlConfigBase;
	class BIC_DLL CtrlConfig
	{
		public:
			CtrlConfig();
			virtual ~CtrlConfig();

			virtual CtrlConfigBase * getCtrl();

			// virtual CtrlConfigBase * find_config(std::string);
			virtual void xml_read(const std::string &, xmlNode *);
			
		protected:
			// std::map < std::string, CtrlConfigBase * > map_config;
			CtrlConfigBase * ctrl;
	};
}

#endif
