#ifndef MODBUS_MSG_FC23_H
#define MODBUS_MSG_FC23_H

#include "modbusmsgheader.h"
#include "polldevice.h"

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
	class MODBUS_DLL ModbusMsgFC23 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC23()
			: ModbusMsgHeader(0x17)
			{}

			virtual ~ModbusMsgFC23()
			{}
			
			virtual uint16_t encodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeQuestion(uint8_t*, uint16_t);
			virtual uint16_t decodeResponse(uint8_t*, uint16_t);
			
		protected:
			uint16_t read_starting_addr;
			uint16_t quantity_to_read;
			uint16_t write_starting_addr;
			uint16_t quantity_to_write;
			uint8_t  write_byte_count;
			uint16_t write_registers_value[256];
			uint8_t  byte_count;
			uint16_t read_registers_value[256];
	};
}

#endif
