#ifndef MODBUS_MSG_FC03_H
#define MODBUS_MSG_FC03_H

#include "modbusmsgheader.h"
#include <vector>

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
	class MODBUS_DLL ModbusMsgFC03 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC03(uint16_t, uint16_t);
			virtual ~ModbusMsgFC03();

			virtual void set(uint16_t, uint16_t);			
			virtual uint16_t get(uint16_t);

			virtual int32_t read(uint8_t *, int32_t);
			virtual int32_t write(uint8_t *, int32_t);

		protected:
			uint16_t _starting_address;
			uint16_t _coils_quantity;
			std::vector < uint16_t > _coils_status;
	};
}

#endif
