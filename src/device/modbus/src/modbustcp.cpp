#include "modbustcp.h"
#include "sockettcp.h"
#include "modbusmsgdirect.h"
#include "modbusexception.h"
#include "polldevice.h"
#include "log.h"
#include <iostream>
#include <sstream>
#include <thread>

Modbus::ModbusTcp::ModbusTcp(PollDevice * socket)
: ModbusChannel(socket)
, _transaction_id(1)
, _protocol_id(0)
{}

Modbus::ModbusTcp::~ModbusTcp()
{}

int32_t Modbus::ModbusTcp::actionIn()
{
	// Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	uint8_t trame[512];
	int32_t len = _device->read(trame, 512);
	if (len > 6)
	{
		uint32_t cpt = 0;
		uint16_t transaction_id = trame[cpt] << 8; ++cpt;
		transaction_id |= trame[cpt]; ++cpt;

		if (transaction_id != _transaction_id)
		{
			std::stringstream ss;
			ss << "reception transaction_id different.";
			throw Modbus::ModbusException(__FILE__, __LINE__, ss.str());
		}

		uint16_t protocol_id = trame[cpt] << 8; ++cpt;
		protocol_id |= trame[cpt]; ++cpt;

		if (protocol_id != _protocol_id)
		{
			std::stringstream ss;
			ss << "reception protocol_id different.";
			throw Modbus::ModbusException(__FILE__, __LINE__, ss.str());
		}

		uint16_t msg_length = trame[cpt] << 8; ++cpt;
		msg_length |= trame[cpt]; ++cpt;

		Modbus::ModbusMsg * msg = new Modbus::ModbusMsg();
		len = msg->in()->write(trame+cpt, len-cpt);
		_fifo_in.push(msg);
	}

	_transaction_id += 1;
	return len;
}

int32_t Modbus::ModbusTcp::actionOut()
{
	// Log::getLogger()->debug(__FILE__, __LINE__, "actionOut");

	ModbusMsg * msg = _fifo_out.front();
	_fifo_out.pop();

	uint16_t cpt = 0;
	uint8_t trame[256];

	trame[cpt] = (_transaction_id >> 8) & 0xFF; ++cpt;
	trame[cpt] = _transaction_id & 0xFF; ++cpt;

	trame[cpt] = (_protocol_id >> 8) & 0xFF; ++cpt;
	trame[cpt] = _protocol_id & 0xFF; ++cpt;

	uint16_t len = msg->out()->read(trame+cpt+2, 256-2-cpt);

	trame[cpt] = (len >> 8) & 0xFF; ++cpt;
	trame[cpt] = len & 0xFF; ++cpt;

	cpt += len;

	return ((Socket::SocketTcp *)_device)->write(trame, cpt);
}

int32_t Modbus::ModbusTcp::actionError()
{}
