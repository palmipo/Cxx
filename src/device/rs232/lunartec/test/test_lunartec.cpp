#include "rs232.h"
#include "lunartec.h"
#include <iostream>
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

int main(int argc, char **argv)
{
 	log4cxx::BasicConfigurator::configure();
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("tcl4tower"));

	if (argc != 3)
	{
		std::cout << argv[0] << " /dev/ttyUSB0 texte" << std::endl;
		return -1;
	}
	
	try
	{
		RS232 uart(argv[1]);
		Lunartec lunartec(1, &uart);
		lunartec.send(argv[2]);
	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
		return -1;
	}

	return 0;
}

