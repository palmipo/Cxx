#ifndef BIC_CANBUS_H
#define BIC_CANBUS_H

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
	class Ctrl;
	class BIC_DLL Canbus
	{
		public:
			// uint8_t getNodeId();
			std::string str_iface;
			std::string str_node_id;
			std::string str_ctrl_id;
			std::string str_config_xml;
			std::string str_protocole;
			
			virtual void xml_read(xmlNode *);
	};
}

#endif
