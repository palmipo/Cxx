#include "modbusmsgdirect.h"
#include <cstring>

Modbus::ModbusMsgDirect::ModbusMsgDirect(uint8_t fct_code)
: ModbusMsgHeader(fct_code)
{}

uint16_t Modbus::ModbusMsgDirect::encodeQuestion()
{
	msg->encodeHeader();
	return 0;
}

uint16_t Modbus::ModbusMsgDirect::decodeQuestion()
{
	msg->decodeHeader();
	return 0;
}

uint16_t Modbus::ModbusMsgDirect::decodeResponse()
{
	msg->decodeHeader();
	return 0;
}
