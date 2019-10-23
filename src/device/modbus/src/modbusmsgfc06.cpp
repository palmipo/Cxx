#include "modbusmsgfc06.h"
#include "modbusmsgexception.h"
#include "log.h"

Modbus::ModbusMsgFC06::ModbusMsgFC06()
: ModbusMsgHeader(0x06)
{}

Modbus::ModbusMsgFC06::~ModbusMsgFC06()
{}

void Modbus::ModbusMsgFC06::setRegister(uint16_t addr, uint16_t value)
{
	data_addr = addr;
	status = value;
}

uint16_t Modbus::ModbusMsgFC06::encodeQuestion()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "encodeQuestion");

	uint16_t cpt = Modbus::ModbusMsgHeader::encodeHeader();

	uint8_t d;
	d = (data_addr & 0xFF00) >> 8;
	cpt += _buffer_out.write(&d, 1, cpt);

	d = data_addr & 0x00FF;
	cpt += _buffer_out.write(&d, 1, cpt);

	d = (status & 0xFF00) >> 8;
	cpt += _buffer_out.write(&d, 1, cpt);

	d = status & 0x00FF;
	cpt += _buffer_out.write(&d, 1, cpt);
	
	return cpt;
}

uint16_t Modbus::ModbusMsgFC06::decodeQuestion()
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeHeader();
/*
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
		status = data[cpt] << 8;
		++cpt;
	}
	if (cpt < len)
	{
		status |= data[cpt];
		++cpt;
	}
*/
	return cpt;
}

uint16_t Modbus::ModbusMsgFC06::decodeResponse()
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeHeader();

	if (functionCode() != 0x06)
	{
		throw Modbus::ModbusMsgException(__FILE__, __LINE__, "reception taille incorrect.");
	}

	uint16_t d = 0;
	uint8_t data;
	cpt += _buffer_in.read(&data, 1, cpt);
	d = data << 8;
	cpt += _buffer_in.read(&data, 1, cpt);
	d |= data;
	if (d != data_addr)
	{
		throw Modbus::ModbusMsgException(__FILE__, __LINE__, "erreur dans la reponse du register");
	}

	uint16_t s = 0;
	cpt += _buffer_in.read(&data, 1, cpt);
	s = data << 8;
	cpt += _buffer_in.read(&data, 1, cpt);
	s |= data;
	if (s != status)
	{
		throw Modbus::ModbusMsgException(__FILE__, __LINE__, "erreur dans la reponse du status");
	}

	return cpt;
}
