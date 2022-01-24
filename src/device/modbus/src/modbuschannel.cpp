#include "modbuschannel.h"
#include "modbusmsg.h"
#include "polldevice.h"
#include "log.h"

Modbus::ModbusChannel::ModbusChannel(PollDevice * device)
: _device(device)
{}

int32_t Modbus::ModbusChannel::readDirect(Modbus::ModbusMsg * msg)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "readDirect");

	uint8_t data[1024];
	int32_t data_length = _device->read(data, 1024);
	
	msg->write(data, data_length);

	return data_length;
}

int32_t Modbus::ModbusChannel::writeDirect(Modbus::ModbusMsg * msg)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "writeDirect");

	uint8_t data[1024];
	
	int32_t cpt = msg->read(data, 1024);

	_device->write(data, cpt);

	return cpt;
}
