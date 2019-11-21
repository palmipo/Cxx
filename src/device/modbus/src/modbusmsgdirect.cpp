#include "modbusmsgdirect.h"
#include <cstring>

Modbus::ModbusMsgDirect::ModbusMsgDirect()
: ModbusMsgHeader()
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
