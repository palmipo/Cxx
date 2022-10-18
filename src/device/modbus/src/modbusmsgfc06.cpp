#include "modbusmsgfc06.h"
#include "modbusmsgexception.h"
#include "codec.h"
#include "log.h"
#include <sstream>

Modbus::ModbusMsgFC06::ModbusMsgFC06(uint16_t address)
: Modbus::ModbusMsgHeader::ModbusMsgHeader(0x06)
, _address(address)
, _value(0)
{}

Modbus::ModbusMsgFC06::~ModbusMsgFC06()
{}

void Modbus::ModbusMsgFC06::set(uint16_t value)
{
	_value = value;
}

uint16_t Modbus::ModbusMsgFC06::get()
{
	return _value;
}

int32_t Modbus::ModbusMsgFC06::read(uint8_t * data, int32_t length)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "read()");

	int32_t cpt = Modbus::ModbusMsgHeader::read(data, length);

Codec codec;
codec.encoder_decoder(data, cpt, &_address, 0, 16);
//	data[cpt] = (_address & 0xFF00) >> 8; ++cpt;
//	data[cpt] = _address & 0x00FF; ++cpt;
cpt += 16;

codec.encoder_decoder(data, cpt, &_value, 0, 16);
//	data[cpt] = (_value & 0xFF00) >> 8; ++cpt;
//	data[cpt] = _value & 0x00FF; ++cpt;
cpt += 16;

	return cpt;
}

int32_t Modbus::ModbusMsgFC06::write(uint8_t * data, int32_t length)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "write()");

	int32_t cpt = Modbus::ModbusMsgHeader::write(data, length);

Codec codec;
codec.encoder_decoder(&_address, 0, data, cpt, 16);	
cpt += 16;
	_address = (data[cpt] << 8) | data[cpt+1]; cpt += 2;

codec.encoder_decoder(&_value, 0, data, cpt, 16);
cpt += 16;
	_value = (data[cpt] << 8) | data[cpt+1]; cpt += 2;

	//~ std::stringstream ss;
	//~ ss << "address : " << std::hex << _address << std::dec << std::endl;
	//~ ss << "value: " << std::hex << _value << std::dec << std::endl;
	//~ Log::getLogger()->debug(__FILE__, __LINE__, ss.str());

	return cpt;
}
