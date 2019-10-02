#include "modbusmsgfc16.h"
#include "modbusmsgexception.h"
#include <cstring>

Modbus::ModbusMsgFC16::ModbusMsgFC16()
: ModbusMsgHeader(0x10)
{}

Modbus::ModbusMsgFC16::~ModbusMsgFC16()
{}

void Modbus::ModbusMsgFC16::setRegister(uint16_t num, uint16_t value)
{
	registers[num] = value;
}

uint16_t Modbus::ModbusMsgFC16::encodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t data_addr = registers.begin()->first;
	uint16_t nb_registers = registers.size();

	uint16_t cpt = Modbus::ModbusMsgHeader::encodeQuestion(data, len);

	if (cpt < len)
	{
		data[cpt] = (data_addr & 0xFF00) >> 8;
		++cpt;
	}
	if (cpt < len)
	{
		data[cpt] = data_addr & 0x00FF;
		++cpt;
	}
	if (cpt < len)
	{
		data[cpt] = (nb_registers & 0xFF00) >> 8;
		++cpt;
	}
	if (cpt < len)
	{
		data[cpt] = nb_registers & 0x00FF;
		++cpt;
	}
	if (cpt < len)
	{
		data[cpt] = nb_registers << 1;
		++cpt;
	}

    for (std::map<uint16_t, uint16_t>::iterator it = registers.begin(); ((cpt<len) && (it != registers.end())); ++it)
    {
        data[cpt] = (it->second & 0xFF00) >> 8; ++cpt;
        data[cpt] = it->second & 0x00FF; ++cpt;
    }

	return cpt;
}
uint16_t Modbus::ModbusMsgFC16::decodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeQuestion(data, len);

	uint16_t data_addr;
	uint16_t nb_registers;
	uint8_t nb_octet;
	if (cpt < len)
	{
		data_addr = data[cpt] << 8;
		++cpt;
	}
	if (cpt < len)
	{
		data_addr |= data[cpt];
		++cpt;
	}
	if (cpt < len)
	{
		nb_registers = data[cpt] << 8;
		++cpt;
	}
	if (cpt < len)
	{
		nb_registers |= data[cpt];
		++cpt;
	}
	if (cpt < len)
	{
		nb_octet = data[cpt];
		++cpt;
		
		if (nb_octet != (nb_registers >> 1))
		{
			throw Modbus::ModbusMsgException(__FILE__, __LINE__, "Modbus::ModbusMsgFC16::decodeQuestion");
		}
	}
    for (uint16_t i=0; ((cpt < len) && (i<nb_registers)); ++i)
    {
        registers[data_addr + i] = data[cpt] << 8;
		++cpt;

        registers[data_addr + i] |= data[cpt];
		++cpt;
    }

	return cpt;
}

uint16_t Modbus::ModbusMsgFC16::decodeResponse(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeResponse(data, len);

	uint16_t data_addr;
	uint16_t nb_registers;
	if (cpt < len)
	{
		data_addr = data[cpt] << 8;
		++cpt;
	}
	if (cpt < len)
	{
		data_addr |= data[cpt];
		++cpt;
	}
	if (data_addr != registers.begin()->first)
	{
		throw Modbus::ModbusMsgException(__FILE__, __LINE__, "erreur de registre dans la reponse");
	}
	if (cpt < len)
	{
		nb_registers = data[cpt] << 8;
		++cpt;
	}
	if (cpt < len)
	{
		nb_registers |= data[cpt];
		++cpt;
	}
	if (nb_registers != registers.size())
	{
		throw Modbus::ModbusMsgException(__FILE__, __LINE__, "erreur du nombre de registre dans la reponse");
	}

	return cpt;
}
