#include "modbusmsgfc05.h"
#include "modbusrtu.h"
#include "modbusexception.h"
#include "pollexception.h"
#include <cstdint>
//~ #include <poll.h>
//~ #include <thread>
#include <sstream>


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::stringstream ss;
		ss << std::string(argv[0]) << " <ip>";
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	try
	{
		RS232 serial(argv[1]);
		serial.configure(B9600, 8, E, 1);
		
		Modbus::ModbusRtu sock1(1, &serial);

		Modbus::ModbusMsgFC05 msg1(16);
		msg1.set(0, 1);
		
		sock1.write(msg1);

		//~ std::stringstream ss;
		//~ Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
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
