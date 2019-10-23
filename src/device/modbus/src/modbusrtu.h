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
			ModbusRtu(PollDevice *);
			virtual ~ModbusRtu();

		protected:
			virtual int32_t actionIn();
			virtual int32_t actionOut();
			virtual int32_t actionError();

		private:
			virtual uint16_t calcul_crc(uint8_t *, int32_t);
	};
}

#endif
