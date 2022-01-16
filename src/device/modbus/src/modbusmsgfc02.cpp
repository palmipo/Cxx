#include "modbusmsgfc02.h"

Modbus::ModbusMsgFC02::ModbusMsgFC02(uint16_t starting_address, uint16_t coils_quantity)
: Modbus::ModbusMsgHeader::ModbusMsgHeader(0x02)
, _starting_address(starting_address)
, _coils_quantity(coils_quantity & 0x7D0)
, _coils_status(std::vector < uint8_t > (coils_quantity))
{}

Modbus::ModbusMsgFC02::~ModbusMsgFC02()
{}

void Modbus::ModbusMsgFC02::set(uint16_t address, uint8_t value)
{
	_coils_status[address] = value;
}

uint8_t Modbus::ModbusMsgFC02::get(uint16_t address)
{
	return _coils_status[address];
}

int32_t Modbus::ModbusMsgFC02::read(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::read(data, length);

	data[cpt] = (_starting_address & 0xFF00) >> 8; ++cpt;
	data[cpt] = _starting_address & 0x00FF; ++cpt;

	data[cpt] = (_coils_quantity & 0xFF00) >> 8; ++cpt;
	data[cpt] = _coils_quantity & 0x00FF; ++cpt;
	
	return cpt;
}

int32_t Modbus::ModbusMsgFC02::write(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::write(data, length);

	uint8_t byte_count = data[cpt];
	cpt += 1;

	int32_t k = 0;
	for (int32_t i=0; (i<byte_count); ++i)
	{
		uint8_t octet = data[i+cpt];
		for (int32_t j=0; j<8; ++j)
		{
			_coils_status[k] = (octet & (1 << j)) ? 1 : 0;
			k += 1;
		}
	}
	
	return cpt;
}
