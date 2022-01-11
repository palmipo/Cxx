#ifndef MODBUS_MSG_FC02_H
#define MODBUS_MSG_FC02_H

#include <map>

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
	class MODBUS_DLL ModbusMsgFC02 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC02(uint16_t, uint16_t);
			virtual ~ModbusMsgFC02();

			virtual void set(uint16_t, uint8_t);			
			virtual uint8_t get(int16_t);

			virtual int32_t read(uint8_t *, int32_t);
			virtual int32_t write(uint8_t *, int32_t);

		protected:
			uint16_t _starting_address;
			uint16_t _coils_quantity;
			std::vector < uint8_t > _coils_status;
	};
}

#endif
