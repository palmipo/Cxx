#ifndef BIC_CTRL_H
#define BIC_CTRL_H

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
	class CtrlConfig;
	class BIC_DLL Ctrl
	{
		public:
			Ctrl();
			virtual ~Ctrl();

			std::string str_ctrl_id;
			std::string str_type;

			virtual CtrlConfig * getCfg();
			virtual void xml_read(xmlNode * a_node);
			// virtual Ctrl& operator=(const Ctrl &);

		protected:
			CtrlConfig * cfg;
	};
}

#endif
