#include "i2c.h"
#include "i2cexception.h"
#include "pcf8583.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int main(int argc, char ** argv)
{
	try
	{
		I2C i2c(argv[1]);

		PCF8583 calandar(0, &i2c);
		calandar.setClock("11:01:00");
		calandar.getClock(buf);
		std::cout << buf << std::endl;
		
		while (1)
		{
			Util::sleep(1000);
		}
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

