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

class Fifo;
class RS232;
namespace Modbus
{
	class ModbusFifo;
	class ModbusMsg;
	class MODBUS_DLL ModbusRtu : public ModbusChannel
	{
		public:
			ModbusRtu(RS232 *);
			virtual ~ModbusRtu();

			virtual int32_t read(uint8_t *, int32_t);
			virtual int32_t read();

			virtual int32_t read(ModbusMsg *);
			virtual int32_t write(ModbusMsg *);
		
			virtual int8_t id_slave() const;
			virtual void set_id_slave(uint8_t);

		protected:
			virtual uint16_t calcul_crc(uint8_t *, int32_t);

		protected:
			uint8_t _module_address;
			Fifo * _fifo;
			ModbusFifo * _lst;
		};
}

#endif
