#include "modbusfactory.h"
#include "modbusmsgfc03.h"
#include "modbuschannel.h"
#include "modbusexception.h"
#include "pollexception.h"
#include <cstdint>
#include <poll.h>
#include <thread>
#include <sstream>


void thread_poll_start(Modbus::ModbusFactory * factory, int32_t * fin)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "DEBUT thread_poll_start");

	while(! *fin)
	{
		try
		{
			factory->scrute(1000, 1, 1, 1);
		}
		catch(Modbus::ModbusException e)
		{
			std::stringstream ss;
			ss << "thread_poll_start exception " << e.what();
			Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		}
		catch(PollException e)
		{
			std::stringstream ss;
			ss << "thread_poll_start exception " << e.what();
			Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		}
		catch(...)
		{
			Log::getLogger()->debug(__FILE__, __LINE__, "thread_poll_start exception");
		}
	}

	Log::getLogger()->debug(__FILE__, __LINE__, "FIN thread_poll_start");
}

void thread_action_start(Modbus::ModbusFactory * factory, int32_t * fin)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "DEBUT thread_action_start");

	while(! *fin)
	{
		try
		{
			factory->actionOut();
			factory->actionIn();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
		catch(Modbus::ModbusException e)
		{
			std::stringstream ss;
			ss << "thread_action_start exception " << e.what();
			Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		}
		catch(PollException e)
		{
			std::stringstream ss;
			ss << "thread_action_start exception " << e.what();
			Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		}
		catch(...)
		{
			Log::getLogger()->debug(__FILE__, __LINE__, "thread_action_start exception");
		}
	}

	Log::getLogger()->debug(__FILE__, __LINE__, "FIN thread_action_start");
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::stringstream ss;
		ss << std::string(argv[0]) << " <ip>";
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}

	int32_t fin = 0;
	Modbus::ModbusFactory factory;

	std::thread t1(thread_poll_start, &factory, &fin);
	std::thread t2(thread_action_start, &factory, &fin);

	try
	{
		// Modbus::ModbusChannel * sock1 = (Modbus::ModbusChannel *)factory.tcp(argv[1]);
		Modbus::ModbusChannel * sock1 = (Modbus::ModbusChannel *)factory.rtu(argv[1], 19200, 1, 1);

		Modbus::ModbusMsgFC03 msg1;
		msg1.setSlaveAddress(0xF8);
		msg1.setRegisterAddr(0xCA8, 1);
		sock1->sendFC(&msg1);
		std::stringstream ss;
		ss << "slave addr : " << (int)msg1.slaveAddress();
		ss << " fonction code : " << (int)msg1.functionCode();
		ss << " error code : " << (int)msg1.errorCode();
		ss << " TCC : " << (int)msg1.getRegister(0xCA8);
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
	catch(Modbus::ModbusException e)
	{
		std::stringstream ss;
		ss << "ModbusException : " << e.what();
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
	catch(PollException e)
	{
		std::stringstream ss;
		ss << "PollException : " << e.what();
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
	}
	catch(...)
	{
		Log::getLogger()->debug(__FILE__, __LINE__, "exception ...");
	}

	// arret du thread secondaire
	fin = 1;
	t1.join();
	t2.join();

	return 0;
}
