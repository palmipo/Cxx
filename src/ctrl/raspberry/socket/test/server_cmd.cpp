#include "socketfactory.h"
#include "socketexception.h"
#include "sockettcp.h"
#include <iostream>
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

// static void reception(void * data)
// {
	// Socket::SocketTcp * server = (Socket::SocketTcp *)data;

	// try
	// {
		// u8 msg[256];
		// s32 len = server->read(msg, 256);

		// u8 rcv[] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x04, 0x06, 0x00, 0x02, 0x00, 0xFF};
		// server->write(rcv, 12);
	// }
	// catch (Socket::SocketException & e) {
		// LOG4CXX_ERROR(logger, e.what());
	// }
// }

// static void connexion(s32 handler, void * data)
// {
	// try
	// {
		// Socket::SocketFactory *fact = (Socket::SocketFactory *)data;
		// Socket::SocketTcp * cnx = (Socket::SocketTcp *) fact->get(handler);
	// }
	// catch (Socket::SocketException & e) {
		// LOG4CXX_ERROR(logger, e.what());
	// }
// }

int main (int argc, char **argv)
{
 	log4cxx::BasicConfigurator::configure();
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger( "main"));

	try
	{
		Socket::SocketFactory factory;
		factory.addTcpServer("0.0.0.0", 502);
		
		while(1)
		{
			factory.scrute(60000);
		}
	}
	catch (Socket::SocketException & e)
	{
		LOG4CXX_ERROR(logger, e.what());
	}

	return 0;
}
