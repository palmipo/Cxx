#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include "sim900.h"

#include <string>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <thread>

static void scrute(SIM900 * gprs, int32_t * fin)
{
	while(! *fin)
	{
		std::cout << "scrute" << std::endl;
		gprs->scrute(1000);
	}
}

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << argc << argv[0] << " </dev/ttyS0> <numero_tel.txt> <message>" << std::endl;
		return -1;
	}
	
	try
	{
		int32_t fin = 0;
		SIM900 gprs(argv[1]);
		std::thread t(scrute, &gprs, &fin);
		t.detach();
		std::this_thread::sleep_for(std::chrono::seconds(1));

		gprs.init_sms();
		
		gprs.list_sms();
		std::this_thread::sleep_for(std::chrono::seconds(10));

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

		std::this_thread::sleep_for(std::chrono::seconds(60));

		fin = 1;
		t.join();
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
