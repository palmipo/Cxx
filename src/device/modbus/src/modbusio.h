#ifndef MODBUSIO_H
#define MODBUSIO_H

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
	class MODBUS_DLL ModbusIo
	{
		public:
			ModbusIo();
			virtual ~ModbusIo();
		
			virtual void read(uint8_t *, int32_t) = 0;
			virtual void write(uint8_t *, int32_t) = 0;
	};
}

#endif
