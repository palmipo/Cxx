#include "modbusfifo.h"
#include "log.h"

Modbus::ModbusFifo::ModbusFifo()
{}

Modbus::ModbusFifo::~ModbusFifo()
{}
		
void Modbus::ModbusFifo::add(uint8_t fc, Modbus::ModbusMsg * msg)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "add");

	std::map<uint8_t, std::list<ModbusMsg *>>::iterator it = _lst.find(fc);
	if (it != _lst.end())
	{
		it->second.push_back(msg);;
	}
}
