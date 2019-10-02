#include "modbusmsg.h"
#include "log.h"

Modbus::ModbusMsg::ModbusMsg()
: _taille_question(0)
, _taille_response(0)
{}

/*
 * return offset
 */
uint16_t Modbus::ModbusMsg::encodeQuestion(uint8_t* data, uint16_t len)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "encodeQuestion");
	_taille_question = _buffer_in.read(data, len);
	return _taille_question;
}

uint16_t Modbus::ModbusMsg::decodeQuestion(uint8_t* data, uint16_t len)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "decodeQuestion");
	_buffer_in.write(data, len);
	return 0;
}

uint16_t Modbus::ModbusMsg::encodeResponse(uint8_t* data, uint16_t len)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "encodeResponse");
	_taille_response = _buffer_out.read(data, len);
	return _taille_response;
}

uint16_t Modbus::ModbusMsg::decodeResponse(uint8_t* data, uint16_t len)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "decodeResponse");
	_buffer_out.write(data, len);
	return 0;
}

uint16_t Modbus::ModbusMsg::tailleQuestion()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "tailleQuestion");
	return _taille_question;
}

uint16_t Modbus::ModbusMsg::tailleResponse()
{
	Log::getLogger()->debug(__FILE__, __LINE__, "tailleResponse");
	return _taille_response;
}
