#include "modbusmsgfc11.h"
#include "modbuschannel.h"
#include <iostream>
#include <iomanip>
#include <cstring>

uint16_t Modbus::ModbusMsgFC11::encodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::encodeHeader();

	return cpt;
}

uint16_t Modbus::ModbusMsgFC11::decodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeHeader();

	return cpt;
}

uint16_t Modbus::ModbusMsgFC11::decodeResponse(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeHeader();

	{
		subfunction = data[cpt] << 8; cpt += 1;
		subfunction |= data[cpt]; cpt += 1;

		subfunction = data[cpt] << 8; cpt += 1;
		subfunction |= data[cpt]; cpt += 1;
	}

	return cpt;
}
