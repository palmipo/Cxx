#ifndef MODBUS_MSG_H
#define MODBUS_MSG_H

#include "modbusbuffer.h"
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

			virtual uint16_t encodeQuestion(uint8_t *, uint16_t);
			virtual uint16_t decodeQuestion(uint8_t *, uint16_t);
			
			virtual uint16_t encodeResponse(uint8_t *, uint16_t);
			virtual uint16_t decodeResponse(uint8_t *, uint16_t);
		
		protected:
			ModbusBuffer _buffer_in;
			ModbusBuffer _buffer_out;
	};
}

#endif
