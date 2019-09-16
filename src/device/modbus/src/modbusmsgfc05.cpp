#include "modbusmsgfc05.h"
#include "modbusmsgexception.h"

void Modbus::ModbusMsgFC05::setStatus(uint16_t value)
{
	status = value;
}

uint16_t Modbus::ModbusMsgFC05::getStatus()
{
	return status;
}

uint16_t Modbus::ModbusMsgFC05::encodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::encode(data, len);

    data[cpt] = (data_addr & 0xFF00) >> 8; ++cpt;
    data[cpt] = data_addr & 0x00FF; ++cpt;

    data[cpt] = (status & 0xFF00) >> 8; ++cpt;
    data[cpt] = status & 0x00FF; ++cpt;

	return cpt;
}
uint16_t Modbus::ModbusMsgFC05::decodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

    data_addr = data[cpt] << 8; ++cpt;
    data_addr |= data[cpt]; ++cpt;

    status = data[cpt] << 8; ++cpt;
    status |= data[cpt]; ++cpt;

	return cpt;
}

uint16_t Modbus::ModbusMsgFC05::decodeResponse(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

	{
		data_addr = data[cpt]; cpt += 1;
		data_addr |= data[cpt] << 8; cpt += 1;

		status = data[cpt]; cpt += 1;
		status |= data[cpt] << 8; cpt += 1;
	}

	return cpt;
}
