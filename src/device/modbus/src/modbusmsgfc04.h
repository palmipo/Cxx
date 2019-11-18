#ifndef MODBUS_MSG_FC04_H
#define MODBUS_MSG_FC04_H

#include "modbusmsgheader.h"

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
	class MODBUS_DLL ModbusMsgFC04 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC04()
			: ModbusMsgHeader(0x04)
			{}

			virtual ~ModbusMsgFC04()
			{}
			
			// + 30001 offset
			virtual void setDataAddr(uint16_t addr) { data_addr = addr; }
			virtual void setNbRegisters(uint16_t nb) { nb_registers = nb; }
			
			virtual void setRegister(uint16_t, uint16_t);
			virtual uint16_t getRegister(uint16_t);

			virtual uint16_t encodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeResponse(uint8_t*, uint16_t);

		protected:
			uint16_t data_addr;
			uint16_t nb_registers;
			uint16_t registers[128];
	};
}

#endif
