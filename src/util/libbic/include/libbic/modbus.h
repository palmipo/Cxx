#ifndef BIC_MODBUS_H
#define BIC_MODBUS_H

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
	class BIC_DLL Modbus
	{
		public:
			// uint8_t getSlaveAddr();
			// void setSlaveAddr(uint8_t addr);

			std::string str_iface;
			std::string str_slave_address;
			std::string str_ctrl_id;
			std::string str_config_xml;
			std::string str_protocole;
			std::string str_carte;
			
			virtual void xml_read(xmlNode *);
	};
}

#endif
