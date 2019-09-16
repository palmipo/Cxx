#include "i2c.h"
#include "i2cexception.h"
#include "saa1064.h"
#include "ds1621.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int main(int argc, char ** argv)
{
	try
	{
		I2C i2c(argv[1]);

		SAA1064 afficheur(2, &i2c);
		afficheur.set_luminosity(7);

		DS1621 temperature(0, &i2c);
		temperature.debut_conversion();

		while (1)
		{
			std::stringstream ss;
			u8 t = temperature.lecture_temperature();
			ss << (int)t << "C";
			afficheur.afficher((s8*)ss.str().c_str(), ss.str().length());

			// Util::sleep(1000);
		}
		
		temperature.fin_conversion();
	}
	catch(I2CException & e)
	{
		std::cout << "exception  " << e.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "exception ..." << std::endl;
	}
	return 0;
}

