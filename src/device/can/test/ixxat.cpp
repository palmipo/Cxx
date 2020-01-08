#include "socketfactory.h"
#include "sockettcp.h"
#include "socketexception.h"
#include "pollexception.h"
#include <iostream>
#include <iomanip>
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

int main(int argc, char **argv)
{
 	log4cxx::BasicConfigurator::configure();
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("ixxat"));

	try
	{
		Socket::SocketFactory factory;
		Socket::SocketTcp * sock0 = factory.addTcpConnection("192.168.1.207", 19227);
		if (sock0)
		{
			const char * msg1 = "C INIT 1000\r\n";

			s32 len = 0;

			LOG4CXX_DEBUG(logger, "ecriture : " << msg1);
			len = sock0->write((u8*)msg1, 13);

			factory.scrute(10000);
		}
	}
	catch(Socket::SocketException e)
	{
		LOG4CXX_ERROR(logger, "exception " << e.what());
	}
	catch(PollException e)
	{
		LOG4CXX_ERROR(logger, "exception " << e.what());
	}
	catch(...)
	{
		LOG4CXX_ERROR(logger, "exception");
	}

	return 0;
}
