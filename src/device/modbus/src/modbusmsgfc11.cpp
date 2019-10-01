#include "modbusmsgfc11.h"
#include "modbuschannel.h"
#include <iostream>
#include <iomanip>
#include <cstring>

uint16_t Modbus::ModbusMsgFC11::encodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::encode(data, len);

	return cpt;
}

uint16_t Modbus::ModbusMsgFC11::decodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

	return cpt;
}

uint16_t Modbus::ModbusMsgFC11::decodeResponse(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

	{
		subfunction = data[cpt] << 8; cpt += 1;
		subfunction |= data[cpt]; cpt += 1;

		subfunction = data[cpt] << 8; cpt += 1;
		subfunction |= data[cpt]; cpt += 1;
	}

	return cpt;
}
