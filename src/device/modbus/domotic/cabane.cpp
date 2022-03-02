#include "r4dcb08.h"
#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include "modbusmsgfc06.h"
#include "modbusrtu.h"
#include "modbusexception.h"
#include "log.h"

#include <sstream>
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << argv[0] << " /dev/ttyUSB0" << std::endl;
		return -1;
	}

	try
	{
		RS232Factory factory;

		RS232 * serial = factory.add(argv[1]);
		serial->setConfig(B9600, 8, 'E', 1);

		Modbus::ModbusRtu rtu(1, serial);
		
		Modbus::R4DCB08 sondes(&rtu);
		Modbus::R4D3B16 relais(&rtu);

		sondes.temperature(0);
		relais.openAll();
		
		return 0;
	}
	catch(Modbus::ModbusException e)
	{
		std::stringstream ss;
		ss << "ModbusException : " << e.what();
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		return -1;
	}
	catch(RS232Exception e)
	{
		std::stringstream ss;
		ss << "RS232Exception : " << e.what();
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		return -1;
	}
	catch(...)
	{
		Log::getLogger()->debug(__FILE__, __LINE__, "exception ...");
		return -1;
	}
}
