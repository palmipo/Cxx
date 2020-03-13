#ifndef BIC_CMDMODBUS_H
#define BIC_CMDMODBUS_H

#include "libbic/command.h"
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
	class BIC_DLL CommandModbus : public Command
	{
		public:
			CommandModbus();
			virtual ~CommandModbus();
		
			uint8_t getReadfct();
			uint8_t getWritefct();
			uint16_t getRegisterValue();
			uint16_t getRegisterNumber();
			uint16_t getMask();
			uint16_t getHighValue();
			uint16_t getLowValue();
			uint16_t getVoltageValue();
			uint16_t getCurrentValue();
		
			std::string str_drive_id;
			std::string str_signal_id;
			std::string str_index;
			std::string str_unite;
			std::string str_plc_id;
			std::string str_iface;
			std::string str_offset;
			std::string str_default_value;

			std::string str_read_fct;
			std::string str_write_fct;
			std::string str_registre;
			std::string str_nb_registre;
			std::string str_mask;
			std::string str_hight_value;
			std::string str_low_value;
			std::string str_voltage_value;
			std::string str_current_value;
			std::string str_voltage_unit;
			std::string str_current_unit;
			
			virtual void xml_read(xmlNode *);
	};
}

#endif
