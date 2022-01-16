#include "modbusmsgdirect.h"
#include <cstdint>
#include <cstring>

Modbus::ModbusMsgDirect::ModbusMsgDirect()
: ModbusMsgHeader(0)
{}

int32_t Modbus::ModbusMsgDirect::set(uint8_t * data, int32_t length)
{
	_length = length;
	std::memcpy(_data, data, _length);
	return _length;
}

int32_t Modbus::ModbusMsgDirect::get(uint8_t * data, int32_t length)
{
	std::memcpy(data, _data, _length);
	return _length;
}

int32_t Modbus::ModbusMsgDirect::write(uint8_t * data, int32_t length)
{
	_length = length;
	std::memcpy(_data, data, _length);
	return _length;
}

int32_t Modbus::ModbusMsgDirect::read(uint8_t * data, int32_t length)
{
	std::memcpy(data, _data, _length);
	return _length;
}
