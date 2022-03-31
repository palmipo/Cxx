#ifndef MODBUSCHANNEL_H
#define MODBUSCHANNEL_H

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

class Device;
namespace Modbus
{
	class ModbusMsg;
	class MODBUS_DLL ModbusChannel
	{
		public:
			ModbusChannel(Device *);

			virtual int32_t read(ModbusMsg *) = 0;
			virtual int32_t write(ModbusMsg *) = 0;
		
		protected:
			Device * _device;
	};
}
#endif
