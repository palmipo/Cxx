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

uint16_t Modbus::ModbusMsgFC03::encodeQuestion()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "encodeQuestion");

	uint32_t cpt = encodeHeader();

	uint8_t d;
	d = (data_addr & 0xFF00) >> 8;
	cpt += _buffer_out.write(&d, 1, cpt);

	d = data_addr & 0x00FF;
	cpt += _buffer_out.write(&d, 1, cpt);

	d = (nb_registers & 0xFF00) >> 8;
	cpt += _buffer_out.write(&d, 1, cpt);

	d = nb_registers & 0x00FF;
	cpt += _buffer_out.write(&d, 1, cpt);

	return cpt;
}

uint16_t Modbus::ModbusMsgFC03::decodeQuestion()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "decodeQuestion");

	uint16_t cpt = decodeHeader();

    //~ // if (cpt < len)
	//~ {
		//~ data_addr = _buffer_out._buffer[cpt] << 8;
		//~ ++cpt;
	//~ }
    //~ // if (cpt < len)
	//~ {
		//~ data_addr |= _buffer_out._buffer[cpt];
		//~ ++cpt;
	//~ }
    //~ // if (cpt < len)
	//~ {
		//~ nb_registers = _buffer_out._buffer[cpt] << 8;
		//~ ++cpt;
	//~ }
    //~ // if (cpt < len)
	//~ {
		//~ nb_registers |= _buffer_out._buffer[cpt];
		//~ ++cpt;
	//~ }

	return cpt;
}

uint16_t Modbus::ModbusMsgFC03::decodeResponse()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "decodeResponse");

	uint32_t cpt = decodeHeader();

	if (functionCode() != 0x03)
	{
		throw Modbus::ModbusMsgException(__FILE__, __LINE__, "reception fonction code incorrect.");
	}

	// number of data bytes to follow
	uint8_t number_of_byte = 0;
	cpt += _buffer_in.read(&number_of_byte, 1, cpt);

	uint16_t nb = number_of_byte >> 1;
	if (nb != nb_registers)
	{
		throw Modbus::ModbusMsgException(__FILE__, __LINE__, "reception taille incorrect.");
	}

	for (uint16_t i=0; (i<nb_registers); ++i)
	{
		uint8_t d[2];
		cpt += _buffer_in.read(d, 2, cpt);
		registers[data_addr + i] = d[0] << 8;
		registers[data_addr + i] |= d[1];
	}

	return cpt;
}
