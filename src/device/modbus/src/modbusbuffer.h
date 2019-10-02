#ifndef MODBUS_BUFFER_H
#define MODBUS_BUFFER_H

#include <cstdint>
#include <queue>

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
	class ModbusMsg;
	class MODBUS_DLL ModbusBuffer
	{
		public:
			ModbusBuffer();
			virtual ~ModbusBuffer();
			
			virtual int32_t write(uint8_t * data, int32_t length);
			virtual int32_t read(uint8_t * data, int32_t length);

		protected:
			std::vector < uint8_t > _buffer;
	};
}

#endif
