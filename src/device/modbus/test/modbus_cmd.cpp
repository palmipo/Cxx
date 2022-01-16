#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include "modbusmsgfc06.h"
#include "modbusrtu.h"
#include "modbusexception.h"
#include "log.h"
#include "polldevice.h"
#include <cstdint>
#include <sstream>
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
		RS232Factory factory;

		RS232 * serial = factory.add(argv[1]);
		serial->setConfig(B9600, 8, 'E', 1);
		
		Modbus::ModbusRtu sock(1, serial);

		//~ Modbus::ModbusMsgFC06 msg1(1);
		//~ msg1.set(0x0200);
		//~ sock.write(&msg1);
		//~ std::this_thread::sleep_for(std::chrono::seconds(1));
		//~ sock.read(&msg1);

		//~ std::this_thread::sleep_for(std::chrono::minutes(1));
		
		Modbus::ModbusMsgFC06 msg2(2);
		msg2.set(0x0640);

		sock.write(&msg2);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		sock.read(&msg2);

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
