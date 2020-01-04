#ifndef MODBUS_MSG_FC72_H
#define MODBUS_MSG_FC72_H

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
	class ModbusMsgFC72 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC72();
			virtual ~ModbusMsgFC72();
			
			virtual void writeIntern(uint8_t, uint64_t, uint8_t *, uint8_t);

			virtual uint16_t encodeQuestion(uint8_t *, uint16_t);
			virtual uint16_t decodeQuestion(uint8_t *, uint16_t);
			virtual uint16_t decodeResponse(uint8_t *, uint16_t);

		protected:
			uint8_t _cpu;
			uint64_t _addr;
			std::map < uint16_t, uint16_t > _values;
	};
}

#endif
