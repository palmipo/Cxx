#ifndef MODBUS_MSG_FC15_H
#define MODBUS_MSG_FC15_H

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
	class MODBUS_DLL ModbusMsgFC15 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC15()
			: ModbusMsgHeader(0x0F)
			{}

			virtual ~ModbusMsgFC15()
			{}
			
			virtual uint16_t encodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeResponse(uint8_t*, uint16_t);

		protected:
			uint16_t data_addr;
			uint16_t nb_coils;
			uint16_t coils[128];
	};
}

#endif
