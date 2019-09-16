#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include "sim900.h"
#include "raspii2c.h"
#include "ada772.h"
#include "hd44780.h"

#include <string>
#include <iostream>
#include <fstream>
#include <poll.h>
#include <cstdint>

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << argv[0] << " </dev/ttyAMA0> <numero_tel.txt> <message>" << std::endl;
		return -1;
	}
	
	try
	{
		RS232Factory factory;
		RS232 * serial = factory.addSerialConnection(argv[1]);
		serial->setConfig(B9600, 8, 'N', 1, 0);
		serial->setInterCharacterTimer(0xFF);
		//~ serial->setBlockingReadUntilCharacter(2);
		
		SIM900 gprs(serial);
		//~ gprs.atz();

		//~ poll(0, 0, 60000);

		gprs.init_sms();
		std::ifstream fic(argv[2], std::ios::in);
		if (fic)
		{
			std::string ligne;
			while (getline(fic, ligne))
			{
				std::cout << ligne << std::endl;
				gprs.send_sms(ligne, argv[3]);
			}
			
			fic.close();
		}
	}
	catch(RS232Exception & e)
	{
		std::cerr << "RS232Exception : " << e.what() << std::endl;
		return -1;
	}
	catch(...)
	{
		std::cerr << "erreur" << std::endl;
		return -1;
	}

	return 0;
}
