#ifndef MODBUS_MSG_HEADER_H
#define MODBUS_MSG_HEADER_H

#include <cstdint>
#include "modbusmsg.h"

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
	class MODBUS_DLL ModbusMsgHeader : public ModbusMsg
	{
		public:
			ModbusMsgHeader(uint8_t);
			virtual ~ModbusMsgHeader();

			virtual uint8_t  functionCode() const;
			virtual uint8_t  errorCode() const;

			virtual uint32_t write() = 0;
			virtual int32_t read() = 0;

		protected:
			uint8_t  _function_code;
			uint8_t  _error_code;
	};
}

#endif
