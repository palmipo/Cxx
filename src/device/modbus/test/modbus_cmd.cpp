#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include "r4d3b16.h"
#include "modbusrtu.h"
#include "modbusexception.h"
#include "log.h"
#include "polldevice.h"
#include <cstdint>
#include <sstream>
#include <iostream>
#include <thread>


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::stringstream ss;
		ss << std::string(argv[0]) << " </dev/ttyUSB0>";
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	try
	{
		uint8_t data[1024];

		RS232Factory factory;

		RS232 * serial = factory.add(argv[1]);
		serial->setConfig(B9600, 8, 'E', 1);
		
		Modbus::ModbusRtu sock(1, serial);

		Modbus::R4D3B16 msg(&sock);
		msg.openAll();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		msg.closeAll();


		return 0;
	}
	catch(Modbus::ModbusException e)
	{
		std::stringstream ss;
		ss << "ModbusException : " << e.what();
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		return -1;
	}
	catch(PollException e)
	{
		std::stringstream ss;
		ss << "PollException : " << e.what();
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		return -1;
	}
	catch(...)
	{
		Log::getLogger()->debug(__FILE__, __LINE__, "exception ...");
		return -1;
	}
}
