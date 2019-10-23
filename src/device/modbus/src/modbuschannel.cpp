#include "polldevice.h"
#include "modbuschannel.h"
#include "modbusmsg.h"
#include "modbusexception.h"
#include "log.h"
#include <thread>
#include <sstream>

Modbus::ModbusChannel::ModbusChannel(PollDevice * device)
: PollDevice(device->handler())
, _device(device)
{}

void Modbus::ModbusChannel::sendFC(ModbusMsg * msg, int32_t max_retry, int32_t timeout)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "sendFC");

	// enregistrement fifo de sortie
	_fifo_out.push(msg);

	// attente presence element fifo entree
	int32_t retry = 0;
	while (_fifo_in.empty() && (retry < max_retry))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
		retry += 1;
	}

	if (_fifo_in.empty())
	{
		throw Modbus::ModbusException(__FILE__, __LINE__, "fifo vide !");
	}
	
	// lecture du message fifo entree
	ModbusMsg * msg_fifo = _fifo_in.front();
	_fifo_in.pop();

	// copie de la reponse dans la question
	uint8_t data[512];
	int32_t length = msg_fifo->in()->read(data, 512);
	msg->in()->write(data, length);

	// liberation message entree
	delete msg_fifo;
}
