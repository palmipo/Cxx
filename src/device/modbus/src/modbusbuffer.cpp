#include "modbusbuffer.h"
#include "modbusmsg.h"
#include "modbusmsgheader.h"
#include "log.h"
#include <sstream>

Modbus::ModbusBuffer::ModbusBuffer()
: _buffer_length(0)
{
	_buffer.resize(512);
}

Modbus::ModbusBuffer::~ModbusBuffer()
{}

int32_t Modbus::ModbusBuffer::write(uint8_t * data, int32_t length, int32_t offset)
{
	int32_t l = (length+offset > _buffer.size()) ? _buffer.size()-offset : length;
	//~ Log::getLogger()->debug(__FILE__, __LINE__, std::to_string(l));

	for(int32_t i=0; i<l; ++i)
	{
		_buffer[i+offset] = data[i];
		_buffer_length+=1;
	}
	
	return l;
}

int32_t Modbus::ModbusBuffer::read(uint8_t * data, int32_t length, int32_t offset)
{
	int32_t l = (length+offset > _buffer_length) ? _buffer_length-offset : length;
	//~ Log::getLogger()->debug(__FILE__, __LINE__, std::to_string(l));

	for(int32_t i=0; ((i<l) && ((i+offset)<_buffer_length)); ++i)
	{
		data[i] = _buffer[i+offset];
	}
	
	return l;
}
