#ifndef MODBUS_MSG_DIRECT_H
#define MODBUS_MSG_DIRECT_H

#include "modbusmsgheader.h"
#include <cstdint>

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
	class MODBUS_DLL ModbusMsgDirect : public ModbusMsgHeader
	{
		public:
			ModbusMsgDirect(uint8_t);

			virtual int32_t set(uint8_t *, int32_t);
			virtual int32_t get(uint8_t *, int32_t);

			virtual int32_t read(uint8_t *, int32_t);
			virtual int32_t write(uint8_t *, int32_t);

		protected:
			uint8_t _data[1024];
			int32_t _length;
	};
}

#endif
