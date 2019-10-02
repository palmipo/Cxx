#include "modbusmsgfc02.h"
#include "modbusmsgexception.h"

Modbus::ModbusMsgFC02::ModbusMsgFC02()
: ModbusMsgHeader(0x02)
{}

Modbus::ModbusMsgFC02::~ModbusMsgFC02()
{}

void Modbus::ModbusMsgFC02::readInputStatus(uint16_t index_first_bit, uint16_t number_of_bits)
{
	for (uint16_t i=0; i<number_of_bits; ++i)
	{
		_bytes[index_first_bit + i] = 0;
	}
}

uint16_t Modbus::ModbusMsgFC02::getDiscretInput(uint16_t addr_coils)
{
	return _bytes[addr_coils];
}

uint16_t Modbus::ModbusMsgFC02::encodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::encodeQuestion(data, len);

	std::map < uint16_t, uint16_t >::iterator it = _bytes.begin();
	if (it != _bytes.end())
	{
		data[cpt] = (it->first & 0xFF00) >> 8; ++cpt;
		data[cpt] = it->first & 0x00FF; ++cpt;

		data[cpt] = (_bytes.size() & 0xFF00) >> 8; ++cpt;
		data[cpt] = _bytes.size() & 0x00FF; ++cpt;
	}

	return cpt;
}
uint16_t Modbus::ModbusMsgFC02::decodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeQuestion(data, len);

	uint16_t data_addr = data[cpt] << 8; ++cpt;
	data_addr |= data[cpt]; ++cpt;

	uint16_t nb_coils = data[cpt] << 8; ++cpt;
	nb_coils |= data[cpt]; ++cpt;

	for (uint16_t i=0; i<nb_coils; ++i)
	{
		_bytes[data_addr + i] = 0;
	}

	return cpt;
}

uint16_t Modbus::ModbusMsgFC02::decodeResponse(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decodeResponse(data, len);

	{
		// number of data bytes to follow
		if (cpt < len)
		{
			uint8_t nb_bytes = data[cpt];
			cpt+=1;
			
			uint16_t nb_coils = nb_bytes << 3;
			if (nb_coils < _bytes.size())
			{
				throw ModbusMsgException(__FILE__, __LINE__, "erreur reception nb coils incorrect");
			}
		}

		uint16_t i = 0;
		std::map < uint16_t, uint16_t > ::iterator it = _bytes.begin();
		while ((it != _bytes.end()) && (cpt < len))
		{
			it->second = ((data[cpt] & (1<<i)) ? 0xFF00 : 0);
			++it;
			i += 1;
			if (i == 8)
			{
				i = 0;
				cpt += 1;
			}
		}
	}

	return cpt;
}
