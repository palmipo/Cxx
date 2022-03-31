#ifndef Modbus_Rtu_H
#define Modbus_Rtu_H

#include "modbuschannel.h"
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

class CtrlUART;
namespace Modbus
{
	class ModbusMsg;
	class MODBUS_DLL ModbusRtu : public ModbusChannel
	{
		public:
			ModbusRtu(CtrlUART *);
			virtual ~ModbusRtu();

			virtual int32_t read(ModbusMsg *);
			virtual int32_t write(ModbusMsg *);
		
			virtual int8_t id_slave() const;
			virtual void set_id_slave(uint8_t);

		protected:
			virtual uint16_t calcul_crc(uint8_t *, int32_t);

		protected:
			CtrlUART * _serial;
			uint8_t _module_address;
		};
}

#endif
