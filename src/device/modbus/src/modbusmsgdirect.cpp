#include "modbusmsgdirect.h"
#include <cstdint>
#include <cstring>

Modbus::ModbusMsgDirect::ModbusMsgDirect(uint8_t fct_code)
: ModbusMsgHeader(fct_code)
{}

int32_t Modbus::ModbusMsgDirect::set(uint8_t * data, int32_t length)
{
	std::memcpy(_data, data, length);
	return _length = length;
}

int32_t Modbus::ModbusMsgDirect::get(uint8_t * data, int32_t length)
{
	std::memcpy(data, _data, length);
	return _length = length;
}

int32_t Modbus::ModbusMsgDirect::read(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::read(data, length);
	std::memcpy(_data, data+cpt, _length-cpt);
	return _length+cpt;
}

int32_t Modbus::ModbusMsgDirect::write(uint8_t * data, int32_t length)
{
	int32_t cpt = Modbus::ModbusMsgHeader::write(data, length);
	std::memcpy(data+cpt, _data, _length);
	return _length+cpt;
}
