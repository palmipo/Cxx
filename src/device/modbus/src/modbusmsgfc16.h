#ifndef MODBUS_MSG_FC16_H
#define MODBUS_MSG_FC16_H

#include "modbusmsgheader.h"
#include <cstdint>
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
	class MODBUS_DLL ModbusMsgFC16 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC16();
			virtual ~ModbusMsgFC16();

			virtual void set(uint16_t, uint8_t);			
			virtual uint8_t get(uint16_t);

			virtual int32_t read(uint8_t *, int32_t);
			virtual int32_t write(uint8_t *, int32_t);

		protected:
			uint16_t _starting_address;
			uint16_t _coils_quantity;
			std::vector < uint8_t > _coils_status;
	};
}

#endif
