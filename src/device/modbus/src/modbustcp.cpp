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

uint16_t Modbus::ModbusTcp::send(ModbusMsg * msg)
{
	uint16_t cpt = 0;
	uint8_t trame[256];

	trame[cpt] = (_transaction_id >> 8) & 0xFF; ++cpt;
	trame[cpt] = _transaction_id & 0xFF; ++cpt;

	trame[cpt] = (_protocol_id >> 8) & 0xFF; ++cpt;
	trame[cpt] = _protocol_id & 0xFF; ++cpt;

	uint16_t len = msg->encodeQuestion(trame+cpt+2, 256-2-cpt);

	trame[cpt] = (len >> 8) & 0xFF; ++cpt;
	trame[cpt] = len & 0xFF; ++cpt;

	cpt += len;

	return ((Socket::SocketTcp *)_device)->write(trame, cpt);
}

Modbus::ModbusMsg * Modbus::ModbusTcp::recv(int32_t max_retry, int32_t timeout)
{
	int32_t retry = 0;
	while (_fifo.empty() && (retry < max_retry))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
		retry += 1;
	}

	if (_fifo.empty())
	{
		throw Modbus::ModbusException(__FILE__, __LINE__, "fifo vide !");
	}
	
	Modbus::ModbusMsg * msg = _fifo.front();
	_fifo.pop();

	return msg;
}

int32_t Modbus::ModbusTcp::actionIn(uint8_t * trame, int32_t len)
{
	// Log::getLogger()->debug(__FILE__, __LINE__, "actionIn");

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

		Modbus::ModbusMsgDirect * msg = new Modbus::ModbusMsgDirect();
		len = msg->decodeResponse(trame+cpt, len-cpt);
		// if ((msg->slaveAddress() == _slave_address) || (msg->slaveAddress() == 0xF8))
		{
			_fifo.push(msg);
		}
		// else
		{
			// std::stringstream ss;
			// ss << "message poubelle id=" << (int)msg->slaveAddress() << " own id=" << (int)_slave_address;
			// Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
			// delete msg;
		}
	}

	_transaction_id += 1;
	return len;
}

int32_t Modbus::ModbusTcp::actionOut(uint8_t *, int32_t)
{}

int32_t Modbus::ModbusTcp::actionError(uint8_t *, int32_t)
{}
