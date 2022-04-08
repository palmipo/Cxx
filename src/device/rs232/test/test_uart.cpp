#include "rs232.h"
#include "pollfactory.h"
#include "poll.h"
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
		serial.setConfig(B9600, 8, 'N', 1, 0);
		serial.setBlockingReadUntilCharacterArrives(5);

		PollFactory poll;
		poll.add(&serial);

		poll.scrute(100);

		uint8_t data[512];
		int32_t length = serial.read(data, 512);
		std::cout << (char*)data << std::endl;

		std::stringstream ss;
		for (int32_t i=2; i<argc; ++i)
		{
			ss << argv[i] << " ";
		}
		serial.write((uint8_t *)ss.str().c_str(), ss.str().length());


	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
		return -1;
	}

	return 0;
}

