#ifndef BIC_CTRLCONFIGIP_H
#define BIC_CTRLCONFIGIP_H

#include "libbic/ctrlconfigbase.h"
// #include "libbic/element.h"

#include <string>
#include <map>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <iostream>

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
	class Element;
	class BIC_DLL CtrlConfigIp : public CtrlConfigBase
	{
		public:
			CtrlConfigIp();
			virtual ~CtrlConfigIp();

			Element * elem_mode;
			Element * elem_address;
			Element * elem_port;
			Element * elem_mask;
			Element * elem_gw;
			
			virtual void xml_read(xmlNode *);
	};
}
#endif
