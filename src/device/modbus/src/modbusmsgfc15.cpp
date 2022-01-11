#include "modbusmsgfc15.h"

Modbus::ModbusMsgFC15::ModbusMsgFC15(uint16_t starting_address, uint16_t coils_quantity)
: Modbus::ModbusMsgHeader::ModbusMsgHeader(0x0F)
, _starting_address(starting_address)
, _quantity_coils(coils_quantity & 0x7B0)
, _coils_status(std::vector < uint8_t > (_coils_status))
{}

Modbus::ModbusMsgFC15::~ModbusMsgFC15()
{}

void Modbus::ModbusMsgFC15::set(uint16_t address, uint8_t value)
{
	int32_t byte = address >> 3;
	int32_t bit = address - (byte << 3);
	_coils_status[byte] = (_coils_status[byte] & ~(1 << bit)) | (value << bit);
}

uint8_t Modbus::ModbusMsgFC15::get(uint16_t address)
{
	int32_t byte = address >> 3;
	int32_t bit = address - (byte << 3);
	return _coils_status[byte] & (1 << bit);
}

int32_t Modbus::ModbusMsgFC15::write(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::write(data, length);

	data[cpt] = (_starting_address & 0xFF00) >> 8; ++cpt;
	data[cpt] = _starting_address & 0x00FF; ++cpt;

	data[cpt] = (_coils_quantity & 0xFF00) >> 8; ++cpt;
	data[cpt] = _coils_quantity & 0x00FF; ++cpt;
	
	int32_t byte_count =  (_coils_quantity >> 3) + 1;
	data[cpt] = byte_count; ++cpt;

	for (int32_t i=0; i<_coils_quantity; ++i)
	{
		data[cpt] = _coils_status[i];
		++cpt;
	}

	return cpt;
}

int32_t Modbus::ModbusMsgFC15::read(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::read(data, length);

	_byte_count = data[cpt];
	cpt += 1;

	
	return cpt;
}
