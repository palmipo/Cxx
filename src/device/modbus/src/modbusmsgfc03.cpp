#include "modbusmsgfc03.h"

Modbus::ModbusMsgFC03::ModbusMsgFC03(uint16_t starting_address, uint16_t coils_quantity)
: Modbus::ModbusMsgHeader::ModbusMsgHeader(0x03)
, _starting_address(starting_address)
, _coils_quantity(coils_quantity & 0x7D)
, _coils_status(std::vector < uint16_t > (_coils_status))
{}

Modbus::ModbusMsgFC03::~ModbusMsgFC03()
{}

void Modbus::ModbusMsgFC03::set(uint16_t address, uint16_t value)
{
	_coils_status[address] = value;
}

uint16_t Modbus::ModbusMsgFC03::get(uint16_t address)
{
	return _coils_status[address];
}

int32_t Modbus::ModbusMsgFC03::read(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::read(data, length);

	data[cpt] = (_starting_address & 0xFF00) >> 8; ++cpt;
	data[cpt] = _starting_address & 0x00FF; ++cpt;

	data[cpt] = (_coils_quantity & 0xFF00) >> 8; ++cpt;
	data[cpt] = _coils_quantity & 0x00FF; ++cpt;
	
	return cpt;
}

int32_t Modbus::ModbusMsgFC03::write(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::write(data, length);

	uint8_t byte_count = data[cpt];
	cpt += 1;

	for (int32_t i=0; i<byte_count; ++i)
	{
		_coils_status[i] = (data[cpt] << 8) | data[cpt+1];
		cpt += 2;
	}
	
	return cpt;
}
