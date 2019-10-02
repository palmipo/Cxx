#include "modbusmsgfc03.h"
#include "modbusmsgexception.h"
#include "log.h"
#include <sstream>

Modbus::ModbusMsgFC03::ModbusMsgFC03()
: ModbusMsgHeader(0x03)
, data_addr(0)
, nb_registers(0)
{}

Modbus::ModbusMsgFC03::~ModbusMsgFC03()
{}

void Modbus::ModbusMsgFC03::setRegisterAddr(uint16_t addr, uint16_t nb)
{
	data_addr = addr;
	nb_registers = (nb > 128) ? 128 : nb;
}

uint16_t Modbus::ModbusMsgFC03::getRegister(uint16_t num)
{
	std::map<uint16_t, uint16_t>::iterator it_reg = registers.find(num);
	if (it_reg != registers.end())
	{
		return it_reg->second;
	}
	
	throw Modbus::ModbusMsgException(__FILE__, __LINE__, "register inconnu.");
}

uint16_t Modbus::ModbusMsgFC03::encodeQuestion(uint8_t* data, uint16_t len)
{
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

	return cpt;
}

uint16_t Modbus::ModbusMsgFC03::decodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeQuestion(data, len);

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

	return cpt;
}

uint16_t Modbus::ModbusMsgFC03::decodeResponse(uint8_t* data, uint16_t len)
{
	{
		std::stringstream ss;
		ss << "decodeResponse => len " << len;
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeResponse(data, len);
	{
		std::stringstream ss;
		ss << "cpt " << (int)cpt << " ; len " << len;
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
	
	{
		// number of data bytes to follow
		uint8_t number_of_byte = 0;
		if (cpt < len)
		{
			number_of_byte = data[cpt];
			cpt+=1;
		}

		uint16_t nb = number_of_byte >> 1;
		{
			std::stringstream ss;
			ss << "nb " << (int)nb << " ; number_of_byte " << (int)number_of_byte;
			Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		}
		if (nb != nb_registers)
		{
			throw Modbus::ModbusMsgException(__FILE__, __LINE__, "reception taille incorrect.");
		}

		for (uint16_t i=0; ((cpt<len) && (i<nb_registers)); ++i)
		{
			registers[data_addr + i] = data[cpt] << 8; cpt += 1;
			registers[data_addr + i] |= data[cpt]; cpt += 1;
		}
	}

	return cpt;
}
