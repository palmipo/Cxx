#ifndef MODBUS_MSG_FC05_H
#define MODBUS_MSG_FC05_H

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
	class MODBUS_DLL ModbusMsgFC05 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC05()
			: ModbusMsgHeader(0x05)
			{}

			virtual ~ModbusMsgFC05()
			{}
			
			// + 1 offset
			virtual void setDataAddr(uint16_t addr) { data_addr = addr; }
			
			virtual void setStatus(uint16_t);
			virtual uint16_t getStatus();

			virtual uint16_t encodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeResponse(uint8_t*, uint16_t);

		protected:
			uint16_t data_addr;
			uint16_t status;
	};
}

#endif
