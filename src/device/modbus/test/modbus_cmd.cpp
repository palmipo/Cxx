#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include "r4d3b16.h"
#include "modbusrtu.h"
#include "modbusfactory.h"
#include "modbusexception.h"
#include "log.h"
#include "polldevice.h"
#include <cstdint>
#include <sstream>
#include <iostream>
#include <thread>

static int action(PollDevice * factory)
{
}

static void scrute(Modbus::ModbusFactory * factory, int32_t * fin)
{
	while (! *fin)
	{
		factory->scrute(1000, 1, 1, 1);
	}
}

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
		int32_t fin = 0;
		uint8_t data[1024];
		Modbus::ModbusFactory factory;
		std::thread t(scrute, &factory, &fin);

		Modbus::ModbusRtu * rtu = (Modbus::ModbusRtu *)factory.rtu(argv[1], 9600, 8, 1, 1);
		rtu->setActionInCallback(action);

		Modbus::R4D3B16 msg(rtu);
		//msg.openAll();
		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//msg.closeAll();

		msg.toggle(1);
		std::cout << (int)msg.read(1) << std::endl;

		fin = 1;
		t.join();
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
