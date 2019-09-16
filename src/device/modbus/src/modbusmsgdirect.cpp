#include "modbusmsgdirect.h"
#include <cstring>

Modbus::ModbusMsgDirect::ModbusMsgDirect()
: ModbusMsgHeader()
, _msg_snd_len(0)
, _msg_rcv_len(0)
{
	::memset(_msg_snd, 0, 512);
	::memset(_msg_rcv, 0, 512);
}

Modbus::ModbusMsgDirect::~ModbusMsgDirect()
{}

uint16_t Modbus::ModbusMsgDirect::encodeQuestion(uint8_t* data, uint16_t len)
{
	uint16_t l = (_msg_snd_len > len) ? len : _msg_snd_len;
	::memcpy(data, _msg_snd, l);
	return l;
}

uint16_t Modbus::ModbusMsgDirect::decodeQuestion(uint8_t* data, uint16_t len)
{
	_msg_snd_len = (len > 512) ? 512 : len;
	::memcpy(_msg_snd, data, _msg_snd_len);
	return _msg_snd_len;
}

uint16_t Modbus::ModbusMsgDirect::decodeResponse(uint8_t* data, uint16_t len)
{
	decode(data, len);
	_msg_rcv_len = (len > 512) ? 512 : len;
	::memcpy(_msg_rcv, data, _msg_rcv_len);
	return _msg_rcv_len;
}

uint16_t Modbus::ModbusMsgDirect::encodeResponse(uint8_t* data, uint16_t len)
{
	uint16_t l = (_msg_rcv_len > len) ? len : _msg_rcv_len;
	::memcpy(data, _msg_rcv, l);
	return l;
}

uint16_t Modbus::ModbusMsgDirect::msgSendLength() const
{
	return _msg_snd_len;
}

uint16_t Modbus::ModbusMsgDirect::msgReceiveLength() const
{
	return _msg_rcv_len;
}
