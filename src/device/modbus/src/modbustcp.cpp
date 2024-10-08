#include "modbustcp.h"
#include "ctrlsocket.h"
#include "modbusmsgheader.h"
#include "modbusexception.h"
#include "log.h"
#include <iostream>
#include <sstream>
//#include <thread>

Modbus::ModbusTcp::ModbusTcp(CtrlSOCKET * socket)
: ModbusChannel(socket)
, _socket(socket)
, _transaction_id(1)
, _protocol_id(0)
{}

Modbus::ModbusTcp::~ModbusTcp()
{}

int32_t Modbus::ModbusTcp::read(ModbusMsg * msg)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

	uint8_t trame[512];
	int32_t len = _socket->read(trame, 512);
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

		len = msg->read(trame+cpt, len-cpt);
	}

	_transaction_id += 1;
	return len;
}

int32_t Modbus::ModbusTcp::write(ModbusMsg * msg)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "actionOut");

	uint16_t cpt = 0;
	uint8_t trame[256];

	trame[cpt] = (_transaction_id >> 8) & 0xFF; ++cpt;
	trame[cpt] = _transaction_id & 0xFF; ++cpt;

	trame[cpt] = (_protocol_id >> 8) & 0xFF; ++cpt;
	trame[cpt] = _protocol_id & 0xFF; ++cpt;

	uint16_t len = msg->write(trame+cpt+2, 256-2-cpt);

	trame[cpt] = (len >> 8) & 0xFF; ++cpt;
	trame[cpt] = len & 0xFF; ++cpt;

	cpt += len;

	return _socket->write(trame, cpt);
}

