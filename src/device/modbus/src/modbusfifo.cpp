#include "modbusfifo.h"

Modbus::ModbusFifo::ModbusFifo()
{}

Modbus::ModbusFifo::~ModbusFifo()
{}
		
void Modbus::ModbusFifo::add(uint8_t id_slave, Modbus::ModbusMsg * msg)
{
	_lst[id_slave] = msg;
}
