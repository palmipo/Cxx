#ifndef MODBUSCHANNEL_H
#define MODBUSCHANNEL_H

#include "towerdevice.h"
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

class PollDevice;
namespace Modbus
{
	class ModbusMsg;
	class ModbusMsgDirect;
	class MODBUS_DLL ModbusChannel : public TowerDevice
	{
		public:
			ModbusChannel(PollDevice *);

			virtual uint16_t sendFC(ModbusMsg *);
			virtual uint16_t recvFC(ModbusMsg *, int32_t = 10, int32_t = 1000);

		protected:
			virtual uint16_t send(ModbusMsg *)=0;
			virtual ModbusMsg * recv(int32_t = 10, int32_t = 1000)=0;

		protected:
			std::queue < ModbusMsg * > _fifo;
	};
}
#endif
