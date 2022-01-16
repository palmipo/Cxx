#include "modbusmsgfc05.h"
#include "modbusmsgexception.h"

Modbus::ModbusMsgFC05::ModbusMsgFC05(uint16_t address)
: Modbus::ModbusMsgHeader::ModbusMsgHeader(0x05)
, _address(address)
, _value(0)
{}

Modbus::ModbusMsgFC05::~ModbusMsgFC05()
{}

void Modbus::ModbusMsgFC05::set(uint16_t value)
{
	_value = value ? 0xFF00 : 0x0000;
}

uint16_t Modbus::ModbusMsgFC05::get()
{
	return _value ? 1 : 0;
}

int32_t Modbus::ModbusMsgFC05::read(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::read(data, length);

	data[cpt] = (_address & 0xFF00) >> 8; ++cpt;
	data[cpt] = _address & 0x00FF; ++cpt;

	data[cpt] = (_value & 0xFF00) >> 8; ++cpt;
	data[cpt] = _value & 0x00FF; ++cpt;
	
	return cpt;
}

int32_t Modbus::ModbusMsgFC05::write(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::write(data, length);
	
	_address = (data[cpt] << 8) | data[cpt+1]; cpt += 2;
	_value = (data[cpt] << 8) | data[cpt+1]; cpt += 2;

	return cpt;
}
