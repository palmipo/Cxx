#ifndef BIC_CTRLCONFIGSERIAL_H
#define BIC_CTRLCONFIGSERIAL_H

#include "libbic/ctrlconfigbase.h"

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
	class BIC_DLL CtrlConfigSerial : public CtrlConfigBase
	{
		public:
			CtrlConfigSerial();

			// int32_t getBaud();
			// int32_t getParity();
			// int32_t getStop();

			std::string str_device;

			std::string str_baud;
			std::string str_data;
			std::string str_parity;
			std::string str_stop;
			
			virtual void xml_read(xmlNode *);
			
			// friend std::ostream& operator<<(std::ostream& os, BIC::CtrlConfigSerial const& obj);
	};
	
	// std::ostream& operator<<(std::ostream& os,  BIC::CtrlConfigSerial const& obj)
	// {
		// write obj to stream
		// os << std::string("iface : ") << obj.str_iface << std::endl;
		// os << std::string("address : ") << obj.str_address << std::endl;
		// os << std::string("port : ") << obj.str_port << std::endl;
		// os << std::string("mask : ") << obj.str_mask << std::endl;
		// os << std::string("gw : ") << obj.str_gw << std::endl;
		// return os;
	// }
}
#endif
