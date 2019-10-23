#include "modbusmsg.h"
#include "log.h"

Modbus::ModbusMsg::ModbusMsg()
{}

Modbus::ModbusBuffer * Modbus::ModbusMsg::in()
{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "in");
	return &_buffer_in;
}

Modbus::ModbusBuffer * Modbus::ModbusMsg::out()
{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "out");
	return &_buffer_out;
}
