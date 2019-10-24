#include "polldevice.h"
#include "modbuschannel.h"
#include "modbusmsg.h"
#include "modbusmsgheader.h"
#include "modbusexception.h"
#include "log.h"
#include <thread>
#include <sstream>

Modbus::ModbusChannel::ModbusChannel(PollDevice * device)
: PollDevice(device->handler())
, _device(device)
{}

void Modbus::ModbusChannel::sendFC(Modbus::ModbusMsg * msg, int32_t max_retry, int32_t timeout)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "sendFC");

	// enregistrement fifo de sortie
	_fifo_out.push(msg);

	// attente presence element fifo entree
	uint8_t slave_address = ((Modbus::ModbusMsgHeader *)msg)->slaveAddress();
	uint8_t function_code = ((Modbus::ModbusMsgHeader *)msg)->functionCode();
	//~ std::stringstream ss;
	//~ ss << (int32_t)slave_address << " " << (int32_t)function_code;
	//~ Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	
	int32_t retry = 0;
	while (_fifo_in.isEmpty(slave_address, function_code) && (retry < max_retry))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
		retry += 1;
	}

	if (_fifo_in.isEmpty(slave_address, function_code))
	{
		throw Modbus::ModbusException(__FILE__, __LINE__, "fifo vide !");
	}
	
	// lecture du message fifo entree
	Modbus::ModbusMsg * msg_fifo = _fifo_in.get(slave_address, function_code);

	// copie de la reponse dans la question
	uint8_t data[512];
	int32_t length = msg_fifo->in()->read(data, 512);
	msg->in()->write(data, length);

	// liberation message entree
	delete msg_fifo;
}
