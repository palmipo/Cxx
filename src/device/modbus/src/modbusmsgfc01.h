#ifndef MODBUS_MSG_FC01_H
#define MODBUS_MSG_FC01_H

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
    class MODBUS_DLL ModbusMsgFC01 : public ModbusMsgHeader
    {
        public:
			ModbusMsgFC01();
			virtual ~ModbusMsgFC01();

			// + 1 offset
			virtual void readCoilStatus(uint16_t, uint16_t);			
			virtual uint16_t getCoilStatus(uint16_t);

			virtual uint16_t encodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeResponse(uint8_t*, uint16_t);
				
		protected:
			std::map < uint16_t, uint16_t > _bytes;
    };
}

#endif
