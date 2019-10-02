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
	
	if (direct)
	{
		uint8_t data[512];
		len = direct->encodeResponse(data, 512);
		msg->decodeResponse(data, len);
		delete direct;
	}

	return len;
}
