#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include <iostream>
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>
#include "batratypes.h"

int main (int argc, char **argv)
{
 	log4cxx::BasicConfigurator::configure();

    try
    {
        RS232Factory factory;
        RS232 * serial = factory.addSerialConnection("/dev/ttyUSB0");
        if (serial)
        {
            serial->setConfig(B115200, 8, 'N', 2);

            factory.scrute(1000);

			int8_t msg[100];
			s32 len = serial->get(msg, 100);
        }
    }
    catch(RS232Exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
