#ifndef MODBUS_MSG_H
#define MODBUS_MSG_H

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
	class MODBUS_DLL ModbusMsg
	{
		public:
			ModbusMsg();            
			virtual ~ModbusMsg();

			virtual uint16_t encodeQuestion(uint8_t *, uint16_t) = 0;
			virtual uint16_t decodeQuestion(uint8_t *, uint16_t) = 0;
			virtual uint16_t decodeResponse(uint8_t *, uint16_t) = 0;
	};
}

#endif
