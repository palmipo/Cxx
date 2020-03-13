#ifndef BIC_POWER_H
#define BIC_POWER_H

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
	class BIC_DLL Power
	{
		public:
			Power();
			virtual ~Power();

			std::string str_plc_id;
			std::string str_modbus_iface;
			std::string str_signal_id;
			std::string str_index_id;

			virtual void xml_read(xmlNode * a_node);
	};
}

#endif
