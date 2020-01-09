#ifndef MODBUS_MSG_FC71_H
#define MODBUS_MSG_FC71_H

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
	class MODBUS_DLL ModbusMsgFC71 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC71();
			virtual ~ModbusMsgFC71();
			
			virtual void readIntern(uint8_t, uint64_t, uint8_t);
			virtual uint16_t value(uint64_t);

			virtual uint16_t encodeQuestion(uint8_t *, uint16_t);
			virtual uint16_t decodeQuestion(uint8_t *, uint16_t);
			virtual uint16_t decodeResponse(uint8_t *, uint16_t);

		protected:
			uint8_t _cpu;
			uint64_t _addr;
			uint8_t _length;
			std::map < uint64_t, uint16_t > _values;
	};
}

#endif
