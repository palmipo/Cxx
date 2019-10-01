#include "modbusbuffer.h"
#include "modbusmsg.h"
#include "modbusmsgheader.h"

Modbus::ModbusBuffer::ModbusBuffer()
{}

Modbus::ModbusBuffer::~ModbusBuffer()
{}

void Modbus::ModbusBuffer::write(uint8_t * data, int32_t length)
{
	for(int32_t i=0; i<length; ++i)
	{
		_buffer.push_back(data[i]);
	}
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

int32_t Modbus::ModbusBuffer::decode(ModbusMsg * msg)
{
	return msg->decodeResponse(_buffer.data(), _buffer.size());
}
