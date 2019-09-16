#include "socketfactorycallback.h"
#include "socketexception.h"
#include "sockettcpcallback.h"
#include <iostream>
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

static void reception(void * data)
{
	Socket::SocketTcp * server = (Socket::SocketTcp *)data;

	try
	{
		u8 msg[256];
		s32 len = server->read(msg, 256);

		u8 rcv[] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x04, 0x06, 0x00, 0x02, 0x00, 0xFF};
		server->write(rcv, 12);
	}
	catch (Socket::SocketException & e) {
		LOG4CXX_ERROR(logger, e.what());
	}
}

static void connexion(s32 handler, void * data)
{
	try
	{
		Socket::SocketFactoryCallback *fact = (Socket::SocketFactoryCallback*)data;
		Socket::SocketTcpCallback * cnx = (Socket::SocketTcpCallback*)fact->get(handler);

		if (cnx)
		{
			cnx->setCallback(reception, cnx);
		}
	}
	catch (Socket::SocketException & e) {
		LOG4CXX_ERROR(logger, e.what());
	}
}

int main (int argc, char **argv)
{
 	log4cxx::BasicConfigurator::configure();
	LoggerPtr logger(Logger::getLogger( "main"));

	try
	{
		Socket::SocketFactoryCallback factory;
		factory.addTcpServer("0.0.0.0", 502);
		factory.setCallback(connexion, &factory);
		
		// while(1)
		{
			factory.scrute(60000);
			factory.scrute(60000);
			factory.scrute(60000);
			factory.scrute(60000);
			factory.scrute(60000);
			factory.scrute(60000);
			factory.scrute(60000);
			factory.scrute(60000);
			factory.scrute(60000);
			factory.scrute(60000);
		}
	}
	catch (Socket::SocketException & e) {
		LOG4CXX_ERROR(logger, e.what());
	}

	return 0;
}
