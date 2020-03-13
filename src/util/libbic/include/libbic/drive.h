#ifndef BIC_DRIVE_H
#define BIC_DRIVE_H

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
	class Power;
	class Modbus;
	class Canbus;
	class BIC_DLL Drive
	{
		public:
			Drive();
			~Drive();

			virtual Power  * getPower();
			virtual Modbus * getModbus(const std::string &);
			virtual Canbus * getCanbus(const std::string &);
			// Signal * find_signal(std::string, std::string);

			std::string str_drive_id;
			std::string str_type;
		
			std::string str_device_feature;
			std::string str_system_feature;

			virtual void xml_read(xmlNode *);
			
		protected:
			std::map < std::string, Modbus * > xml_modbus;
			std::map < std::string, Canbus * > xml_canbus;
			// std::map < std::tuple < std::string, std::string >, XmlSignal * > map_signaux;
			Power * power;
			
	};
}

#endif
