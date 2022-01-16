#include "modbusmsgfc06.h"
#include "modbusmsgexception.h"
#include "log.h"

Modbus::ModbusMsgFC06::ModbusMsgFC06(uint16_t address)
: Modbus::ModbusMsgHeader::ModbusMsgHeader(0x06)
, _address(address)
, _value(0)
{}

Modbus::ModbusMsgFC06::~ModbusMsgFC06()
{}

void Modbus::ModbusMsgFC06::set(uint16_t value)
{
	_value = value;
}

uint16_t Modbus::ModbusMsgFC06::get()
{
	return _value;
}

int32_t Modbus::ModbusMsgFC06::read(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::read(data, length);

	data[cpt] = (_address & 0xFF00) >> 8; ++cpt;
	data[cpt] = _address & 0x00FF; ++cpt;

	data[cpt] = (_value & 0xFF00) >> 8; ++cpt;
	data[cpt] = _value & 0x00FF; ++cpt;
	
	return cpt;
}

int32_t Modbus::ModbusMsgFC06::write(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::write(data, length);

	
	_address = (data[cpt] << 8) | data[cpt+1]; cpt += 2;
	_value = (data[cpt] << 8) | data[cpt+1]; cpt += 2;

	
	return cpt;
}
