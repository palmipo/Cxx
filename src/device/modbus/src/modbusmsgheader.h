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
			ModbusMsgHeader(uint8_t = 0);
			virtual ~ModbusMsgHeader();

			virtual uint32_t encodeHeader();
			virtual uint32_t decodeHeader();

			virtual uint8_t  functionCode() const;
			virtual uint8_t  errorCode() const;

			virtual void setSlaveAddress(uint8_t );
			virtual uint8_t slaveAddress() const;

		protected:
			uint8_t  _slave_address;
			uint8_t  _function_code;
			uint8_t  _error_code;
	};
}

#endif
