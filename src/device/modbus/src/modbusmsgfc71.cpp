#include "modbusmsgfc71.h"
#include "modbusmsgexception.h"
#include <iostream>
#include <cstring>

Modbus::ModbusMsgFC71::ModbusMsgFC71()
: ModbusMsgHeader(0x47)
, _length(0)
{}

Modbus::ModbusMsgFC71::~ModbusMsgFC71()
{}

void Modbus::ModbusMsgFC71::readIntern(uint8_t cpu, uint64_t addr, uint8_t length)
{
	_cpu = cpu;
	_addr = addr;
	_length = length;
}

uint16_t Modbus::ModbusMsgFC71::value(uint64_t i)
{
	std::map < uint64_t, uint16_t >::iterator it = _values.find(i);
	if (it != _values.end())
	{
		return it->second;
	}
	
	throw ModbusMsgException(__FILE__, __LINE__, "élément inconnu.");
}

uint16_t Modbus::ModbusMsgFC71::encodeQuestion(uint8_t * data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::encodeQuestion(data, len);

	if (cpt < len)
	{
		data[cpt] = _cpu; ++cpt;
	}
	if (cpt < len)
	{
		data[cpt] = 0x00; ++cpt;
	}
	if (cpt < len)
	{
		data[cpt] = 0x00; ++cpt;
	}
	if (cpt < len)
	{
		data[cpt] = 0x00; ++cpt;
	}
	if (cpt < len)
	{
		data[cpt] = 0x00; ++cpt;
	}
	if (cpt < len)
	{
		data[cpt] = (_addr & 0xFF000000) >> 24; ++cpt;
	}
	if (cpt < len)
	{
		data[cpt] = (_addr & 0x00FF0000) >> 16; ++cpt;
	}
	if (cpt < len)
	{
		data[cpt] = (_addr & 0x0000FF00) >> 8; ++cpt;
	}
	if (cpt < len)
	{
		data[cpt] = (_addr & 0x000000FF); ++cpt;
	}
	if (cpt < len)
	{
		data[cpt] = _length; ++cpt;
	}

	return cpt;
}

uint16_t Modbus::ModbusMsgFC71::decodeQuestion(uint8_t * data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeQuestion(data, len);

	if (cpt < len)
	{
		_cpu = data[cpt];
		cpt += 1;
	}
	if (cpt < len)
	{
		cpt += 1;
	}
	if (cpt < len)
	{
		cpt += 1;
	}
	if (cpt < len)
	{
		cpt += 1;
	}
	if (cpt < len)
	{
		cpt += 1;
	}
	if (cpt < len)
	{
		_addr = data[cpt] << 24;
		cpt += 1;
	}
	if (cpt < len)
	{
		_addr |= data[cpt] << 26;
		cpt += 1;
	}
	if (cpt < len)
	{
		_addr |= data[cpt] << 8;
		cpt += 1;
	}
	if (cpt < len)
	{
		_addr |= data[cpt];
		cpt += 1;
	}
	if (cpt < len)
	{
		_length = data[cpt];
		cpt += 1;
	}

	return cpt;
}

uint16_t Modbus::ModbusMsgFC71::decodeResponse(uint8_t * data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeResponse(data, len);

	{
		uint8_t nb = 0;
		if (cpt < len)
		{
			nb = data[cpt];
			cpt += 1;
		}

		if (nb != _length)
		{
			throw ModbusMsgException(__FILE__, __LINE__, "reponse incorrecte");
		}
		
		if (nb == 1)
		{
			_values[_addr] = data[cpt]; ++cpt;
		}
		else
		{
			uint8_t nb_byte = nb >> 1;
			for (uint8_t i=0; ((cpt < len) && (i < nb_byte)); ++i)
			{
				_values[_addr + i] = data[cpt] << 8; ++cpt;
				_values[_addr + i] |= data[cpt]; ++cpt;
			}
		}
	}

	return cpt;
}
