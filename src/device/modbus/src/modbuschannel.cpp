#include "polldevice.h"
#include "modbuschannel.h"
#include "modbusmsg.h"
#include "modbusexception.h"
#include "log.h"
#include <thread>
#include <sstream>

Modbus::ModbusChannel::ModbusChannel(PollDevice * device)
: TowerDevice(device)
{}

uint16_t Modbus::ModbusChannel::sendFC(ModbusMsg * msg)
{
	return send(msg);
}

uint16_t Modbus::ModbusChannel::recvFC(ModbusMsg * msg, int32_t max_retry, int32_t timeout)
{
	try
	{
		ModbusMsg * direct = (ModbusMsg *)recv(max_retry, timeout);

		uint8_t data[512];
		direct->decodeResponse(data, 512);

		msg->encodeResponse(data, direct->tailleResponse());
		delete direct;
	}
	catch(Modbus::ModbusException)
	{
	}

	return 0;
}
