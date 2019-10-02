#include "modbusmsgfc15.h"
#include "modbuschannel.h"
#include <iostream>
#include <cstring>

uint16_t Modbus::ModbusMsgFC15::encodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::encodeQuestion(data, len);

    data[cpt] = (data_addr & 0xFF00) >> 8; ++cpt;
    data[cpt] = data_addr & 0x00FF; ++cpt;

    data[cpt] = (nb_coils & 0xFF00) >> 8; ++cpt;
    data[cpt] = nb_coils & 0x00FF; ++cpt;

    uint16_t num_bit = 0;
    uint16_t num_octet = 0;
    for (uint16_t num_bit=0; num_bit<nb_coils; ++num_bit)
    {
        num_octet = num_bit >> 3;
        data[cpt + num_octet] |= ((coils[num_bit] ? 1 : 0) << (num_bit % 8));
    }
    cpt += num_octet + 1;

	return cpt;
}
uint16_t Modbus::ModbusMsgFC15::decodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeQuestion(data, len);

    data_addr = data[cpt] << 8; ++cpt;
    data_addr |= data[cpt]; ++cpt;

    nb_coils = data[cpt] << 8; ++cpt;
    nb_coils |= data[cpt]; ++cpt;

    uint16_t num_bit = 0;
    uint16_t num_octet = 0;
    for (uint16_t num_bit=0; num_bit<nb_coils; ++num_bit)
    {
        num_octet = num_bit >> 3;
        coils[num_bit] = ((data[cpt + num_octet] >> (num_bit % 8)) & 0x01) ? 1 : 0;
    }
    cpt += num_octet + 1;

	return cpt;
}

uint16_t Modbus::ModbusMsgFC15::decodeResponse(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeResponse(data, len);

	{
		// number of data bytes to follow
		data_addr = data[cpt]; cpt += 1;
		data_addr |= data[cpt] << 8; cpt += 1;

		nb_coils = data[cpt]; cpt += 1;
		nb_coils |= data[cpt] << 8; cpt += 1;
	}

	return cpt;
}
