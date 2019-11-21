#include "socketfactory.h"
#include "sockettcp.h"
#include "socketexception.h"
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

int main(int argc, char **argv)
{
	log4cxx::BasicConfigurator::configure();
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger( "main"));

	if (argc != 2)
	{
		LOG4CXX_ERROR(logger, argv[0] << " <ip>");
	}

	try
	{
		Socket::SocketFactory factory;
		Socket::SocketTcp * sock = (Socket::SocketTcp *)factory.addTcpConnection(argv[1], 502);
		if (sock)
		{
			u8 msg[] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0xF8, 0x10, 0x00, 0x01, 0x02, 0x00, 0xFF};

			s32 len = sock->write(msg, 13);
			factory.scrute(10000);
			u8 rep[100];
			len = sock->read(rep, 100);
		}
	}
	catch(Socket::SocketException e)
	{
		LOG4CXX_ERROR(logger, "exception " << e.what());
	}
	catch(...)
	{
		LOG4CXX_ERROR(logger, "exception.");
	}

	return 0;
}
