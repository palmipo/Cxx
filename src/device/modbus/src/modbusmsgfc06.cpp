#include "modbusmsgfc06.h"
#include "modbusmsgexception.h"

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

uint16_t Modbus::ModbusMsgFC06::encodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::encode(data, len);

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
		data[cpt] = (status & 0xFF00) >> 8;
		++cpt;
	}
	if (cpt < len)
	{
		data[cpt] = status & 0x00FF;
		++cpt;
	}
	
	return cpt;
}

uint16_t Modbus::ModbusMsgFC06::decodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

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
	
	return cpt;
}

uint16_t Modbus::ModbusMsgFC06::decodeResponse(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

	{
		uint16_t d = 0;
		if (cpt < len)
		{
			d = data[cpt] << 8; cpt += 1;
		}
		if (cpt < len)
		{
			d |= data[cpt]; cpt += 1;
		}
		if (d != data_addr)
		{
			throw Modbus::ModbusMsgException(__FILE__, __LINE__, "erreur dans la reponse du register");
		}

		uint16_t s = 0;
		if (cpt < len)
		{
			s = data[cpt] << 8; cpt += 1;
		}
		if (cpt < len)
		{
			s |= data[cpt]; cpt += 1;
		}
		if (s != status)
		{
			throw Modbus::ModbusMsgException(__FILE__, __LINE__, "erreur dans la reponse du status");
		}
	}

	return cpt;
}
