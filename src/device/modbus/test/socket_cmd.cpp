#include "socketfactory.h"
#include "sockettcp.h"
#include "socketexception.h"
#include <cstdint>
#include <poll.h>
#include <thread>
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

int fin;

static void * thread_start(void * data)
{
	Socket::SocketFactory * factory = (Socket::SocketFactory *)data;

	while(!fin)
	{
		factory->scrute(1000);
	}
    // Socket::SocketTcp * sock = (Socket::SocketTcp *)data;
    // u8 rep[100];
    // s32 len = sock->read(rep, 100);
}

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
			fin = 0;
			std::thread t1(thread_start, &factory);
			t1.detach();
			
			u8 msg1[] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0xF8, 0x10, 0x00, 0x01, 0x02, 0x00, 0xFF};

            s32 len = sock->write(msg1, 12);
        }
		
		poll(0, 0, 10);
		fin = 1;
    }
    catch(Socket::SocketException e)
    {
        LOG4CXX_ERROR(logger, "exception " << e.what());
    }

    return 0;
}
