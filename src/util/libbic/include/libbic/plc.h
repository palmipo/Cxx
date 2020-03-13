#ifndef BIC_PLC_H
#define BIC_PLC_H

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
	class Modbus;
	class Canbus;
	class Signal;
	class BIC_DLL Plc
	{
		public:
			Plc();
			~Plc();

			Modbus * getModbus(const std::string &);
			Canbus * getCanbus(const std::string &);
			Signal * find_signal(const std::string &);

			std::string str_plc_id;
		
			std::map < std::string, Modbus * > map_modbus;
			std::map < std::string, Canbus * > map_canbus;
			std::map < std::string, Signal * > map_signaux;
			
			virtual void xml_read(xmlNode *);
	};
}

#endif
