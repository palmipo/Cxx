#include "rs232.h"
#include "raspiuart.h"
#include "lunartec.h"
#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		std::cout << argv[0] << " /dev/ttyUSB0 texte" << std::endl;
		return -1;
	}
	
	try
	{
		RS232 serial(argv[1]);
		serial.setConfig(B9600, 8, 'N', 1, 1);

		RaspiUart uart(&serial);
		Lunartec lunartec(1, &uart);
		
		std::stringstream ss;
		for (int32_t i=2; i<argc; ++i)
		{
			ss << argv[i] << " ";
		}
		lunartec.send(ss.str());
	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
		return -1;
	}

	return 0;
}

