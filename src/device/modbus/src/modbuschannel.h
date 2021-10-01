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

#include "polldevice.h"
#include "modbusqueue.h"
#include <queue>

class PollDevice;
namespace Modbus
{
	class ModbusMsg;
	// class ModbusMsgDirect;
	class MODBUS_DLL ModbusChannel : public PollDevice
	{
		public:
			ModbusChannel(PollDevice *);

			virtual void sendFC(ModbusMsg *, int32_t = 10, int32_t = 1000);

		// virtual pur dans PollDevice
		protected:
			virtual int32_t read(uint8_t *, int32_t)
			{ return 0; }

			virtual int32_t write(uint8_t *, int32_t)
			{ return 0; }

		protected:
			ModbusQueue _fifo_in;
			std::queue < ModbusMsg * > _fifo_out;
			PollDevice * _device;
	};
}
#endif
