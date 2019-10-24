#ifndef Modbus_Queue_H
#define Modbus_Queue_H

#include <map>
#include <queue>

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
	class ModbusMsg;
	class MODBUS_DLL ModbusQueue
	{
		public:
			ModbusQueue();
			virtual ~ModbusQueue();
		
			virtual int32_t isEmpty(uint8_t, uint8_t);
			virtual ModbusMsg * get(uint8_t, uint8_t);

			virtual void add(uint8_t, uint8_t, ModbusMsg *);

		protected:
			std::map < std::pair < uint8_t, uint8_t > , std::queue < ModbusMsg * > > _fifo;
	};
}

#endif
