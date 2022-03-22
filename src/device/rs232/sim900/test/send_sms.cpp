#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include "sim900.h"
#include "tempo.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <thread>

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << argc << argv[0] << " </dev/ttyS0> <numero_tel.txt> <message>" << std::endl;
		return -1;
	}
	
	try
	{
		RS232Factory fact;
		RS232 * serial = fact.add(argv[1]);

		SIM900 gprs(serial);

		Tempo::secondes(1);

		gprs.init_sms();
		
		gprs.list_sms();
		Tempo::secondes(10);

		std::ifstream fic(argv[2], std::ios::in);
		if (fic)
		{
			std::string ligne;
			while (getline(fic, ligne))
			{
				std::cout << ligne << std::endl;
				gprs.write_sms(ligne, argv[3]);
			}
			
			fic.close();
		}

		Tempo::secondes(60);
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
