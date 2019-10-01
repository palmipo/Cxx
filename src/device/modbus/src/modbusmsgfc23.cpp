#include "modbusmsgfc23.h"
#include "modbuschannel.h"
#include <iostream>
#include <cstring>

uint16_t Modbus::ModbusMsgFC23::encodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::encode(data, len);

	read_starting_addr = data[cpt] << 8; ++cpt;
	read_starting_addr |= data[cpt]; ++cpt;

	quantity_to_read = data[cpt] << 8; ++cpt;
	quantity_to_read |= data[cpt]; ++cpt;

	write_starting_addr = data[cpt] << 8; ++cpt;
	write_starting_addr |= data[cpt]; ++cpt;

	quantity_to_write = data[cpt] << 8; ++cpt;
	quantity_to_write |= data[cpt]; ++cpt;

	write_byte_count = data[cpt]; ++cpt;

	for (uint16_t i=0; i<write_byte_count; i+=1)
	{
		write_registers_value[i] = data[cpt] << 8; ++cpt;
		write_registers_value[i] |= data[cpt]; ++cpt;
	}

	return cpt;
}
uint16_t Modbus::ModbusMsgFC23::decodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

	data[cpt] = read_starting_addr >> 8; ++cpt;
	data[cpt] = read_starting_addr & 0x00FF; ++cpt;

	data[cpt] = quantity_to_read >> 8; ++cpt;
	data[cpt] = quantity_to_read & 0x00FF; ++cpt;

	data[cpt] = write_starting_addr >> 8; ++cpt;
	data[cpt] = write_starting_addr & 0x00FF; ++cpt;

	data[cpt] = quantity_to_write >> 8; ++cpt;
	data[cpt] = quantity_to_write & 0x00FF; ++cpt;

	data[cpt] = write_byte_count = data[cpt]; ++cpt;

	for (uint16_t i=0; i<write_byte_count; i+=1)
	{
		data[cpt] = write_registers_value[i] >> 8; ++cpt;
		data[cpt] = write_registers_value[i] & 0x00FF; ++cpt;
	}

	return cpt;
}

uint16_t Modbus::ModbusMsgFC23::decodeResponse(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

	{
		byte_count = data[cpt]; ++cpt;
		
		for (uint16_t i=0; i<byte_count; i+=1)
		{
			read_registers_value[i] = data[cpt] << 8; ++cpt;
			read_registers_value[i] |= data[cpt]; ++cpt;
		}
	}

	return cpt;
}
