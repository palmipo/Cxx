#ifndef Modbus_Rtu_H
#define Modbus_Rtu_H

#include "modbuschannel.h"

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
	class MODBUS_DLL ModbusRtu : public ModbusChannel
	{
		public:
			ModbusRtu(uint8_t, PollDevice *);
			virtual ~ModbusRtu();

		protected:
			virtual uint16_t send(ModbusMsg *);
			virtual ModbusMsg * recv(int32_t = 10, int32_t = 1000);

			virtual int32_t actionIn(uint8_t *, int32_t);
			virtual int32_t actionOut(uint8_t *, int32_t);
			virtual int32_t actionError(uint8_t *, int32_t);

		private:
			virtual uint16_t calcul_crc(uint8_t *, int32_t);
	};
}

#endif
