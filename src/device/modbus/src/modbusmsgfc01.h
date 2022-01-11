#ifndef MODBUS_MSG_FC01_H
#define MODBUS_MSG_FC01_H

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
	class MODBUS_DLL ModbusMsgFC01 : public ModbusMsgHeader
	{
		public:
			ModbusMsgFC01(uint16_t);
			virtual ~ModbusMsgFC01();

			virtual void set(uint8_t);			
			virtual uint8_t get();

			virtual int32_t read(uint8_t *, int32_t);
			virtual int32_t write(uint8_t *, int32_t);

		protected:
			uint16_t _address;
			uint8_t _status;
	};
}

#endif
