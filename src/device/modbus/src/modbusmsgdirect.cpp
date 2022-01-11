#include "modbusmsgdirect.h"
#include <cstring>

Modbus::ModbusMsgDirect::ModbusMsgDirect(uint8_t fct_code)
: ModbusMsgHeader(fct_code)
{}

in32_t Modbus::ModbusMsgDirect::set(uint8_t * data, int32_t length)
{
	_length = std::memcpy(_data, data, length);
	return _length;
}

int32_t Modbus::ModbusMsgDirect::get(uint8_t * data, int32_t length)
{
	int32_t l = std::memcpy(data, _data, length);
	return l;
}

in32_t Modbus::ModbusMsgDirect::read(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::read(data, length)
	int32_t l = std::memcpy(_data, data+cpt, length-cpt);
	return l+cpt;
}

int32_t Modbus::ModbusMsgDirect::write(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::write(data, length);
	int32_t l = std::memcpy(data+cpt, _data, _length);
	return l+cpt;
}
