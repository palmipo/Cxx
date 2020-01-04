#include "modbusmsgfc16.h"
#include "modbusmsgexception.h"
#include "endianness.h"
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

uint16_t Modbus::ModbusMsgFC16::encodeQuestion()
{
	Endianness<uint16_t> endian;
	uint16_t data_addr = registers.begin()->first;
	uint16_t nb_registers = registers.size();

	uint16_t cpt = encodeHeader();

	//if (cpt < len)
	{
		uint16_t d = endian.toBigEndian(data_addr);
		cpt += _buffer_out.write((uint8_t*)&d, 2, cpt);
	}
	//if (cpt < len)
	{
		uint16_t d = endian.toBigEndian(nb_registers);
		cpt += _buffer_out.write((uint8_t*)&d, 2, cpt);
	}

	for (std::map<uint16_t, uint16_t>::iterator it = registers.begin(); (/*(cpt<len) &&*/ (it != registers.end())); ++it)
	{
		uint16_t d = endian.toBigEndian(it->second);
		cpt += _buffer_out.write((uint8_t*)&d, 2, cpt);
	}

	return cpt;
}

uint16_t Modbus::ModbusMsgFC16::decodeQuestion()
{
/*
	uint16_t cpt = decodeHeader();

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
*/
return 0;
}

uint16_t Modbus::ModbusMsgFC16::decodeResponse()
{
	Endianness<uint16_t> endian;
	uint16_t cpt = decodeHeader();

	if (functionCode() != 0x10)
	{
		throw Modbus::ModbusMsgException(__FILE__, __LINE__, "reception fonction code incorrect.");
	}

	uint16_t data_addr;
	//if (cpt < len)
	{
		uint16_t d = endian.toBigEndian(data_addr);
		cpt += _buffer_in.read((uint8_t*)&d, 2, cpt);
	}
	if (data_addr != registers.begin()->first)
	{
		throw Modbus::ModbusMsgException(__FILE__, __LINE__, "erreur de registre dans la reponse");
	}
	
	uint16_t nb_registers;
	//if (cpt < len)
	{
		uint16_t d = endian.toBigEndian(nb_registers);
		cpt += _buffer_in.read((uint8_t*)&d, 2, cpt);
	}
	if (nb_registers != registers.size())
	{
		throw Modbus::ModbusMsgException(__FILE__, __LINE__, "erreur du nombre de registre dans la reponse");
	}

	return cpt;
}
