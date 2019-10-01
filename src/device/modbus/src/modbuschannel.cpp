#include "polldevice.h"
#include "modbuschannel.h"
#include "modbusmsgdirect.h"
#include "modbusexception.h"
#include "log.h"
#include <thread>

Modbus::ModbusChannel::ModbusChannel(uint8_t slv_addr, PollDevice * device)
: TowerDevice(device)
, _slave_address(slv_addr)
{}

uint16_t Modbus::ModbusChannel::sendFC(ModbusMsg * msg)
{
	return send(msg);
}

uint16_t Modbus::ModbusChannel::recvFC(ModbusMsg * msg, int32_t max_retry, int32_t timeout)
{
	uint16_t len = 0;
	ModbusMsgDirect * direct = (ModbusMsgDirect *)recv(max_retry, timeout);
	
	if (direct && (direct->msgReceiveLength() > 0))
	{
		uint8_t data[512];
		len = direct->encodeResponse(data, 512);
		msg->decodeResponse(data, len);
		delete direct;
	}

	return len;
}

uint16_t Modbus::ModbusChannel::sendDirect(uint8_t *data, uint16_t nb, int32_t calcul_crc)
{
	ModbusMsgDirect * modbus_msg = new ModbusMsgDirect();
	if (calcul_crc)
	{
		modbus_msg->decodeQuestion(data, nb);
	}
	else
	{
		modbus_msg->decodeQuestion(data, nb-2);
	}

	return send(modbus_msg);
}

uint16_t Modbus::ModbusChannel::receiveDirect(uint8_t * data, uint16_t nb, int32_t max_retry, int32_t timeout)
{
	uint16_t len = 0;
	ModbusMsgDirect * msg = (ModbusMsgDirect *)recv(max_retry, timeout);
	
	if (msg && (msg->msgReceiveLength() > 0))
	{
		len = msg->encodeResponse(data, nb);
		msg->decode(data, len);
		delete msg;
	}

	return len;
}
