#ifndef MODBUS_MSG_FC06_H
#define MODBUS_MSG_FC06_H

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
	class MODBUS_DLL ModbusMsgFC06 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC06(uint16_t);
			virtual ~ModbusMsgFC06();
			
			virtual void set(uint16_t);			
			virtual uint16_t get();

			virtual int32_t read(uint8_t *, int32_t);
			virtual int32_t write(uint8_t *, int32_t);

		protected:
			uint16_t _address;
			uint16_t _value;
	};
}

#endif
