#ifndef MODBUS_MSG_FC03_H
#define MODBUS_MSG_FC03_H

#include "modbusmsgheader.h"
#include <map>

#if defined __MINGW32__ ||  defined __CYGWIN__
	#ifdef MAKE_MODBUS_DLL
		#define MODBUS_DLL __declspec(dllexport)
	#else
		#define MODBUS_DLL __declspec(dllimport)
	#endif
#else
	#define MODBUS_DLL
#endif

namespace Modbus
{
	class MODBUS_DLL ModbusMsgFC03 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC03();
			virtual ~ModbusMsgFC03();

			// + 40001 offset

			// question
			virtual void setRegisterAddr(uint16_t, uint16_t);
			
			// reponse
			virtual uint16_t getRegister(uint16_t);
			
			// codec
			virtual uint16_t encodeQuestion();
			virtual uint16_t decodeQuestion();
			virtual uint16_t decodeResponse();

		protected:
			uint16_t data_addr;
			uint16_t nb_registers;
			std::map<uint16_t, uint16_t> registers;
	};
}

#endif
