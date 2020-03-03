#include "modbusmsgdirect.h"
#include <cstring>

Modbus::ModbusMsgDirect::ModbusMsgDirect(uint8_t fct_code)
: ModbusMsgHeader(fct_code)
{}

uint16_t Modbus::ModbusMsgDirect::encodeQuestion()
{
	encodeHeader();
	return 0;
}

uint16_t Modbus::ModbusMsgDirect::decodeQuestion()
{
	decodeHeader();
	return 0;
}

uint16_t Modbus::ModbusMsgDirect::decodeResponse()
{
	decodeHeader();
	return 0;
}
