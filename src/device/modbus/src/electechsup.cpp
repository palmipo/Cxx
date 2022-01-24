#include "electechsup.h"

Modbus::ElecTechSup::ElecTechSup()
: Modbus::ModbusFactory()
, _can(0)
, _input(0)
, _output(0)
{}

Modbus::ElecTechSup::~ElecTechSup()
{
	delete _can;
	delete _input;
	delete _output;
}

int32_t Modbus::ElecTechSup::actionIn(PollDevice * device)
{
	uint8_t data[1024];
	int32_t length = device->read(data, 1024);
	
	switch (data[0]) // id_slave
	{
		case 1: // out
			_output->write(data+1, length-1);
			break;
		
		case 2: // in
			_input->write(data+1, length-1);
			break;
		
		case 3: // can
			_can->write(data+1, length-1);
			break;
		
		default:
			break;
	}
	
	return length;
}
