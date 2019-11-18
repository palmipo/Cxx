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

#include "modbusbuffer.h"
#include <cstdint>

namespace Modbus
{
	class MODBUS_DLL ModbusMsg
	{
		public:
			ModbusMsg();

			virtual ModbusBuffer * in();
			virtual ModbusBuffer * out();
			
		protected:
			ModbusBuffer _buffer_in;
			ModbusBuffer _buffer_out;
	};
}

#endif
