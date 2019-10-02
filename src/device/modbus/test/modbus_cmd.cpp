#include "modbusfactory.h"
#include "modbusmsgfc03.h"
#include "modbuschannel.h"
#include "modbusexception.h"
#include "pollexception.h"
#include <cstdint>
#include <poll.h>
#include <thread>
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>


static void * thread_start(Modbus::ModbusFactory * factory, int32_t * fin)
{
	Log::getLogger()->debug(__FILE__, __LINE__, "DEBUT thread");

	while(! *fin)
	{
		try
		{
			factory->scrute(1000);
		}
		catch(Modbus::ModbusException e)
		{
			//~ Log::getLogger()->debug(__FILE__, __LINE__, "thread exception " << e.what());
		}
		catch(PollException e)
		{
			//~ Log::getLogger()->debug(__FILE__, __LINE__, "thread exception " << e.what());
		}
		catch(...)
		{
			Log::getLogger()->debug(__FILE__, __LINE__, "thread exception");
		}
	}

	Log::getLogger()->debug(__FILE__, __LINE__, "FIN thread");
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		//~ Log::getLogger()->debug(__FILE__, __LINE__, std::string(argv[0]) << " <ip>");
	}

	try
	{
		int32_t fin = 0;

		Modbus::ModbusFactory factory;
		// Modbus::ModbusChannel * sock = (Modbus::ModbusChannel *)factory.tcp(argv[1]);
		Modbus::ModbusChannel * sock1 = (Modbus::ModbusChannel *)factory.rtu(argv[1], 19200, 1, 1);

		std::thread t1(thread_start, &factory, &fin);
		t1.detach();

		Modbus::ModbusMsgFC03 msg1;
		msg1.setSlaveAddress(0xF8);
		msg1.setRegisterAddr(0xCA8, 1);

		uint16_t len = 0;
		len = sock1->sendFC(&msg1);

		len = sock1->recvFC(&msg1);
		if (len)
		{
			//~ Log::getLogger()->debug(__FILE__, __LINE__, "sock->recvFC() : " << len);
			//~ Log::getLogger()->debug(__FILE__, __LINE__, "slave addr : " << (int)msg1.slaveAddress());
			//~ Log::getLogger()->debug(__FILE__, __LINE__, "fonction code : " << (int)msg1.functionCode());
			//~ Log::getLogger()->debug(__FILE__, __LINE__, "error code : " << (int)msg1.errorCode());
			//~ Log::getLogger()->debug(__FILE__, __LINE__, "TCC : " << (int)msg1.getRegister(11101));
		}

		std::this_thread::sleep_for(std::chrono::seconds(60));

		// arret du thread secondaire
		fin = 1;
		t1.join();
	}
	catch(Modbus::ModbusException e)
	{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "ModbusException : " << e.what());
	}
	catch(PollException e)
	{
	//~ Log::getLogger()->debug(__FILE__, __LINE__, "PollException : " << e.what());
	}
	catch(...)
	{
	Log::getLogger()->debug(__FILE__, __LINE__, "exception ...");
	}

	return 0;
}
