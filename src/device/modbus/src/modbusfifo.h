#ifndef MODBUSFIFO_H
#define MODBUSFIFO_H

#include <map>
#include <list>
#include <cstdint>

namespace Modbus
{
	class ModbusMsg;
	class ModbusFifo
	{
		public:
			ModbusFifo();
			virtual ~ModbusFifo();
		
			virtual void add(uint8_t, ModbusMsg *);
		
		protected:
			std::map<uint8_t, std::list<ModbusMsg *>> _lst;
	};
}

#endif
