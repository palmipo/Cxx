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

int fin;

static void * thread_start(void * data)
{
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("thread"));

	LOG4CXX_DEBUG(logger, "DEBUT thread");

		Modbus::ModbusFactory * factory = (Modbus::ModbusFactory *)data;

	while(!fin)
	{
		try
		{
			factory->scrute(1000);
		}
		catch(Modbus::ModbusException e)
		{
			LOG4CXX_ERROR(logger, "thread exception " << e.what());
		}
		catch(PollException e)
		{
			LOG4CXX_ERROR(logger, "thread exception " << e.what());
		}
		catch(...)
		{
			LOG4CXX_ERROR(logger, "thread exception");
		}
	}

	LOG4CXX_DEBUG(logger, "FIN thread");
}

int main(int argc, char **argv)
{
 	log4cxx::BasicConfigurator::configure();
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger( "main"));

    if (argc != 2)
    {
        LOG4CXX_ERROR(logger, std::string(argv[0]) << " <ip>");
    }

    try
    {
		Modbus::ModbusFactory factory;
        // Modbus::ModbusChannel * sock = (Modbus::ModbusChannel *)factory.tcp(argv[1]);
        Modbus::ModbusChannel * sock1 = (Modbus::ModbusChannel *)factory.rtu(argv[1], 19200, 1, 1);
        Modbus::ModbusChannel * sock2 = (Modbus::ModbusChannel *)factory.rtu(argv[2], 19200, 1, 1);

		fin = 0;
		std::thread t1(thread_start, &factory);
		t1.detach();
		
		Modbus::ModbusMsgFC03 msg1;
		msg1.setSlaveAddress(0xF8);
		msg1.setRegisterAddr(11101, 1);

        LOG4CXX_DEBUG(logger, "sock->sendFC()");
		u16 len = 0;
		len = sock1->sendFC(&msg1);
		len = sock2->sendFC(&msg1);

		// factory.scrute(1000);
		
		// attente de la reponse
        // LOG4CXX_DEBUG(logger, "poll()");
		poll(0, 0, 5000);
		
		len = sock1->recvFC(&msg1);
		if (len)
		{
        LOG4CXX_DEBUG(logger, "sock->recvFC() : " << len);
        LOG4CXX_DEBUG(logger, "slave addr : " << (int)msg1.slaveAddress());
        LOG4CXX_DEBUG(logger, "fonction code : " << (int)msg1.functionCode());
        LOG4CXX_DEBUG(logger, "error code : " << (int)msg1.errorCode());
        LOG4CXX_DEBUG(logger, "TCC : " << (int)msg1.getRegister(11101));
		}
		
		len = sock2->recvFC(&msg1);
        if (len)
		{
		LOG4CXX_DEBUG(logger, "sock->recvFC() : " << len);
        LOG4CXX_DEBUG(logger, "slave addr : " << (int)msg1.slaveAddress());
        LOG4CXX_DEBUG(logger, "fonction code : " << (int)msg1.functionCode());
        LOG4CXX_DEBUG(logger, "error code : " << (int)msg1.errorCode());
        LOG4CXX_DEBUG(logger, "TCC : " << (int)msg1.getRegister(11101));
		}

		// uint8_t data[512];
		// len = sock->receiveDirect(data, 512);
		
		// arret du thread secondaire
		fin = 1;
        // LOG4CXX_DEBUG(logger, "thread::join()");
		t1.join();
		
		poll(0, 0, 1000);
    }
    catch(Modbus::ModbusException e)
    {
        LOG4CXX_ERROR(logger, "ModbusException : " << e.what());
    }
    catch(PollException e)
    {
        LOG4CXX_ERROR(logger, "PollException : " << e.what());
    }
    catch(...)
    {
        LOG4CXX_ERROR(logger, "exception ...");
    }

    return 0;
}
