#include "modbusmsg.h"
#include "log.h"

Modbus::ModbusMsg::ModbusMsg(uint8_t fc)
: _function_code(fc)
{}

Modbus::ModbusMsg::~ModbusMsg()
{}

uint8_t Modbus::ModbusMsg::getFc() const
{
	return _function_code;
}

void Modbus::ModbusMsg::fc(uint8_t fc)
{
	_function_code = fc;
}
