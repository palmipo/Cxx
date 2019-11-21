// #include "socketfactory.h"
#include "canopen.h"
#include "pollexception.h"

#include <iostream>
#include <iomanip>

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

int main(int argc, char **argv)
{
 	log4cxx::BasicConfigurator::configure();
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger( "main"));

    if (argc != 2)
    {
        LOG4CXX_ERROR(logger, argv[0] << " <if>");
    }

    try
    {
        // Socket::SocketFactory factory;
		CANOpen * sock = new CANOpen();
        if (sock)
        {
			sock->connexion(argv[1]);
			
			uint8_t cmd[] = { 0x81, 0, 0, 0, 0, 0, 0, 0, 0 };
			sock->write(cmd, 9);

			uint8_t msg[512];
            // if (factory.scrute(10000) > 0)
			{
				s32 len = sock->read(msg, 512);
			}
        }
    }
    catch(PollException e)
    {
        LOG4CXX_ERROR(logger, "exception " << e.what());
    }

    return 0;
}
