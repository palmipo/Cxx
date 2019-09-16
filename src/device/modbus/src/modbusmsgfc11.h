#ifndef MODBUS_MSG_FC11_H
#define MODBUS_MSG_FC11_H

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
	class MODBUS_DLL ModbusMsgFC11 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC11()
			: ModbusMsgHeader(0x0B)
			{}

			virtual ~ModbusMsgFC11()
			{}
			
			virtual uint16_t encodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeResponse(uint8_t*, uint16_t);
		
		protected:
			uint16_t subfunction;
	};
}

#endif
