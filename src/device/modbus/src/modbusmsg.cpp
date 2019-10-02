#include "modbusmsg.h"

Modbus::ModbusMsg::ModbusMsg()
{}

uint16_t Modbus::ModbusMsg::encodeQuestion(uint8_t* data, uint16_t len)
{
	return _buffer_in.read(data, len);
}

uint16_t Modbus::ModbusMsg::decodeQuestion(uint8_t* data, uint16_t len)
{
	_buffer_in.write(data, len);
}

uint16_t Modbus::ModbusMsg::encodeResponse(uint8_t* data, uint16_t len)
{
	return _buffer_out.read(data, len);
}

uint16_t Modbus::ModbusMsg::decodeResponse(uint8_t* data, uint16_t len)
{
	_buffer_out.write(data, len);
}
