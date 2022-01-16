#include "modbusmsgfc15.h"
#include "log.h"
#include <sstream>

Modbus::ModbusMsgFC15::ModbusMsgFC15(uint16_t starting_address, uint16_t coils_quantity)
: Modbus::ModbusMsgHeader::ModbusMsgHeader(0x0F)
, _starting_address(starting_address)
, _coils_quantity(coils_quantity)
, _coils_status(std::vector < uint8_t > ((coils_quantity>>3)+1))
{}

Modbus::ModbusMsgFC15::~ModbusMsgFC15()
{}

void Modbus::ModbusMsgFC15::set(uint16_t address, uint8_t value)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "set");

	int32_t byte = address >> 3;
	{
		std::stringstream ss;
		ss << "byte : " << byte;
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	int32_t bit = address - (byte << 3);
	{
		std::stringstream ss;
		ss << "bit : " << bit;
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	_coils_status[byte] = (_coils_status[byte] & ~(1 << bit)) | ((value?1:0) << bit);
	{
		std::stringstream ss;
		ss << "_coils_status[byte] : " << (int)_coils_status[byte] << std::endl;
		ss << "_coils_status[byte] : " << (int)(_coils_status[byte] & ~(1 << bit)) << std::endl;
		ss << "_coils_status[byte] : " << (int)((_coils_status[byte] & ~(1 << bit)) | ((value?1:0) << bit)) << std::endl;
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
}

uint8_t Modbus::ModbusMsgFC15::get(uint16_t address)
{
	int32_t byte = address >> 3;
	int32_t bit = address - (byte << 3);
	return _coils_status[byte] & (1 << bit);
}

int32_t Modbus::ModbusMsgFC15::read(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::read(data, length);

	data[cpt] = (_starting_address & 0xFF00) >> 8; ++cpt;
	data[cpt] = _starting_address & 0x00FF; ++cpt;
	{
		std::stringstream ss;
		ss << "_starting_address : " << _starting_address;
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	data[cpt] = (_coils_quantity & 0xFF00) >> 8; ++cpt;
	data[cpt] = _coils_quantity & 0x00FF; ++cpt;
	{
		std::stringstream ss;
		ss << "_coils_quantity : " << _coils_quantity;
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	int8_t byte_count =  (_coils_quantity >> 3) + 1;
	data[cpt] = byte_count; ++cpt;
	{
		std::stringstream ss;
		ss << "byte_count : " << (int)byte_count;
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	for (int8_t i=0; i<byte_count; ++i)
	{
		data[cpt+i] = _coils_status[i];
		{
			std::stringstream ss;
			ss << "data[cpt+i] : " << (int)data[cpt+i];
			Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		}
	}

	return cpt + byte_count;
}

int32_t Modbus::ModbusMsgFC15::write(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::write(data, length);

	_starting_address = data[cpt] << 8; cpt += 1;
	_starting_address |= data[cpt]; cpt += 1;
	_coils_quantity = data[cpt] << 8; cpt += 1;
	_coils_quantity |= data[cpt]; cpt += 1;

	return cpt;
}
