#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include <iostream>

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << argv[0] << " <device>" << std::endl;
		return -1;
	}

    try
    {
        RS232Factory factory;
        RS232 * serial = factory.addSerialConnection(argv[1]);
        if (serial)
        {
            serial->setConfig(B115200, 8, 'N', 1);

			serial->set((int8_t*)"coucou", 6);

            factory.scrute(1000);

			int8_t msg[100];
			int32_t len = serial->get(msg, 100);
			std::cout << "reception (" << len << ") : " << msg << std::endl;
        }
    }
    catch(RS232Exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
