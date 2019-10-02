#include "modbusbuffer.h"
#include "modbusmsg.h"
#include "modbusmsgheader.h"
#include "log.h"
#include <sstream>

Modbus::ModbusBuffer::ModbusBuffer()
{}

Modbus::ModbusBuffer::~ModbusBuffer()
{}

int32_t Modbus::ModbusBuffer::write(uint8_t * data, int32_t length)
{
	_buffer.resize(length);

	for(int32_t i=0; i<length; ++i)
	{
		_buffer.push_back(data[i]);
	}
	
	return length;
}

int32_t Modbus::ModbusBuffer::read(uint8_t * data, int32_t length)
{
	int32_t t = (length > _buffer.size()) ? _buffer.size() : length;

	for(int32_t i=0; i<t; ++i)
	{
		data[i] = _buffer[i];
	}
	
	return t;
}
