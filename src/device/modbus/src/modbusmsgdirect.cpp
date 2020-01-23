#include "modbusmsgdirect.h"
#include <cstring>

Modbus::ModbusMsgDirect::ModbusMsgDirect(uint8_t fct_code)
: ModbusMsgHeader(fct_code)
{}

uint16_t Modbus::ModbusMsgDirect::encodeQuestion()
{
  return 0;
}

uint16_t Modbus::ModbusMsgDirect::decodeQuestion()
{
  return 0;
}

uint16_t Modbus::ModbusMsgDirect::decodeResponse()
{
  return 0;
}
