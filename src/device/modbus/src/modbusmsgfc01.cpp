#include "modbusmsgfc01.h"
#include "modbusmsgexception.h"

Modbus::ModbusMsgFC01::ModbusMsgFC01()
: ModbusMsgHeader(0x01)
{}

Modbus::ModbusMsgFC01::~ModbusMsgFC01()
{}

void Modbus::ModbusMsgFC01::readCoilStatus(uint16_t addr, uint16_t nb)
{
	for (uint16_t i=0; i<nb; ++i)
	{
		_bytes[addr + i] = 0;
	}
}

uint16_t Modbus::ModbusMsgFC01::getCoilStatus(uint16_t addr)
{
	return _bytes[addr];
}

uint16_t Modbus::ModbusMsgFC01::encodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::encode(data, len);

	std::map < uint16_t, uint16_t > ::iterator it = _bytes.begin();
	if (it != _bytes.end())
	{
		data[cpt] = (it->first & 0xFF00) >> 8; ++cpt;
		data[cpt] = it->first & 0x00FF; ++cpt;

		data[cpt] = (_bytes.size() & 0xFF00) >> 8; ++cpt;
		data[cpt] = _bytes.size() & 0x00FF; ++cpt;
	}

	return cpt;
}

uint16_t Modbus::ModbusMsgFC01::decodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

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

uint16_t Modbus::ModbusMsgFC01::decodeResponse(uint8_t* data, uint16_t len)
{
	uint16_t cpt = Modbus::ModbusMsgHeader::decode(data, len);

	{
		// number of data bytes to follow
		if (cpt < len)
		{
			uint8_t nb_bytes = data[cpt];
			cpt+=1;
			
			uint16_t nb_coils = nb_bytes << 3;
			
			if (nb_coils < _bytes.size())
			{
				throw ModbusMsgException(__FILE__, __LINE__, "erreur dans le nombre de coils de la reponse");
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
