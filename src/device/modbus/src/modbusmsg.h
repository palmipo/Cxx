#ifndef MODBUS_MSG_H
#define MODBUS_MSG_H

#if defined __MINGW32__ ||  defined __CYGWIN__
	#ifdef MAKE_MODBUS_DLL
		#define MODBUS_DLL __declspec(dllexport)
	#else
		#define MODBUS_DLL __declspec(dllimport)
	#endif
#else
	#define MODBUS_DLL
#endif

#include <cstdint>

namespace Modbus
{
	class MODBUS_DLL ModbusMsg
	{
		public:
			ModbusMsg();
			virtual ~ModbusMsg();

			virtual int32_t read(uint8_t *, int32_t) = 0;
			virtual int32_t write(uint8_t *, int32_t) = 0;
	};
}

#endif
