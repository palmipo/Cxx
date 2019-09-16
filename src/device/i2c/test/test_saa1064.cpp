#include "rs232factory.h"
#include "rs232.h"
#include "usb_i2c.h"
#include "saa1064.h"
#include "i2cexception.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>
#include <ctime>

int main(int argc, char **argv)
{
	try
	{
		RS232Factory factory;
		RS232 * uart = factory.add(argv[1]);
		UsbI2C i2c(uart);

		SAA1064 afficheur(0, &i2c);

		uint8_t status = afficheur.status();
		std::cout << "status : " << (int)status << std::endl;

		afficheur.test_afficheurs(1);
		std::this_thread::sleep_for(std::chrono::seconds(2));
		afficheur.test_afficheurs(0);

		while(1)
		{
			time_t tt;
			time(&tt);
			struct tm * t = localtime(&tt);
			std::stringstream ss;
			ss << std::setw(2) << std::setfill('0') << t->tm_hour;
			ss << ":";
			ss << std::setw(2) << std::setfill('0') << t->tm_min;
			afficheur.afficher(ss.str().c_str(), (uint8_t)5);
			std::this_thread::sleep_for(std::chrono::seconds(2));

			afficheur.afficher("20°c", (uint8_t)4);
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
	}
	catch(...)
	{
		std::cout << "erreur ..." << std::endl;
	}

	return 0;
}
