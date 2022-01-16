#include "modbusmsgfc16.h"
#include "modbusmsgexception.h"
#include <cstring>

Modbus::ModbusMsgFC16::ModbusMsgFC16()
: ModbusMsgHeader(0x10)
{}

Modbus::ModbusMsgFC16::~ModbusMsgFC16()
{}

void Modbus::ModbusMsgFC16::set(uint16_t num, uint16_t value)
{
	_registers[num] = value;
}

uint16_t Modbus::ModbusMsgFC16::get(uint16_t num)
{
	return _registers[num];
}

int32_t Modbus::ModbusMsgFC16::read(uint8_t * data, int32_t length)
{
	return 0;
}

int32_t Modbus::ModbusMsgFC16::write(uint8_t * data, int32_t length)
{
	return 0;
}
