#include "modbusmsgfc72.h"
#include "modbusmsgexception.h"
#include <iostream>
#include <cstring>

Modbus::ModbusMsgFC72::ModbusMsgFC72()
: ModbusMsgHeader(0x48)
{}

Modbus::ModbusMsgFC72::~ModbusMsgFC72()
{}

void Modbus::ModbusMsgFC72::writeIntern(uint8_t cpu, uint64_t addr, uint8_t * data, uint8_t length)
{
	_cpu = cpu;
	_addr = addr;
	for (uint8_t i=0; i<length; ++i)
	{
		_values[addr + i] = data[i];
	}
}

uint16_t Modbus::ModbusMsgFC72::encodeQuestion(uint8_t * data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::encode(data, len);

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
		data[cpt] = _values.size(); ++cpt;
	}
	for (uint32_t i=0; i<_values.size(); ++i)
	{
		data[cpt] = _values[_addr + i]; ++cpt;
	}

	return cpt;
}

uint16_t Modbus::ModbusMsgFC72::decodeQuestion(uint8_t * data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

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
	
	uint32_t length = 0;
	if (cpt < len)
	{
		length = data[cpt];
		cpt += 1;
	}
	for (uint32_t i=0; i<length; ++i)
	{
		_values[_addr + i] = data[cpt]; ++cpt;
	}

	return cpt;
}

uint16_t Modbus::ModbusMsgFC72::decodeResponse(uint8_t * data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

	{
		uint8_t cpu, length;
		uint64_t addr;

		if (cpt < len)
		{
			cpu = data[cpt];
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
			addr = data[cpt] << 24;
			cpt += 1;
		}
		if (cpt < len)
		{
			addr |= data[cpt] << 26;
			cpt += 1;
		}
		if (cpt < len)
		{
			addr |= data[cpt] << 8;
			cpt += 1;
		}
		if (cpt < len)
		{
			addr |= data[cpt];
			cpt += 1;
		}
		if (cpt < len)
		{
			length = data[cpt];
			cpt += 1;
		}
		
		if ((cpu != _cpu) && (length != _values.size()) && (addr != _addr))
			throw ModbusMsgException(__FILE__, __LINE__, "erreur message reponse");
	}

	return cpt;
}
