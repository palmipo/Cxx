#include "modbusmsgfc04.h"
#include "modbusmsgexception.h"

void Modbus::ModbusMsgFC04::setRegister(uint16_t num, uint16_t value)
{
	if (num < 128)
	{
		registers[num] = value;
	}
}

uint16_t Modbus::ModbusMsgFC04::getRegister(uint16_t num_coils)
{
	return registers[nb_registers];
}

uint16_t Modbus::ModbusMsgFC04::encodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::encode(data, len);

    data[cpt] = (data_addr & 0xFF00) >> 8; ++cpt;
    data[cpt] = data_addr & 0x00FF; ++cpt;

    data[cpt] = (nb_registers & 0xFF00) >> 8; ++cpt;
    data[cpt] = nb_registers & 0x00FF; ++cpt;

	return cpt;
}
uint16_t Modbus::ModbusMsgFC04::decodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

    data_addr = data[cpt] << 8; ++cpt;
    data_addr |= data[cpt]; ++cpt;

    nb_registers = data[cpt] << 8; ++cpt;
    nb_registers |= data[cpt]; ++cpt;

	return cpt;
}

uint16_t Modbus::ModbusMsgFC04::decodeResponse(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

	{
		// number of data bytes to follow
		uint8_t number_of_byte = data[cpt];
		cpt+=1;

		nb_registers = number_of_byte >> 1;

		for (uint16_t num_coil=0; num_coil<nb_registers; ++num_coil)
		{
			registers[num_coil] = data[cpt] << 8; cpt += 1;
			registers[num_coil] |= data[cpt]; cpt += 1;
		}
	}

	return cpt;
}
