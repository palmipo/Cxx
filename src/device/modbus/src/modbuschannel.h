#ifndef MODBUSCHANNEL_H
#define MODBUSCHANNEL_H

#if defined __MINGW32__ ||  defined __CYGWIN__
	#ifdef MAKE_MODBUS_DLL
		#define MODBUS_DLL __declspec(dllexport)
	#else
		#define MODBUS_DLL __declspec(dllimport)
	#endif
#else
	#define MODBUS_DLL
#endif

class PollDevice;
namespace Modbus
{
	// class ModbusMsgDirect;
	class MODBUS_DLL ModbusChannel
	{
		public:
			ModbusChannel(PollDevice *);

			virtual int32_t read(uint8_t *, int32_t) = 0;
			virtual int32_t write(uint8_t *, int32_t) = 0;
		
		protected:
			PollDevice * _device;
	};
}
#endif
