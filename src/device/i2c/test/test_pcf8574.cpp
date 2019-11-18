#include "i2c.h"
#include "i2cexception.h"
#include "pia.h"
#include "pcf8574at.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int main(int argc, char ** argv)
{
	try
	{
		I2C i2c(argv[1]);

		PCF8574AT pia(0, &i2c);
		pia.set(0, 0x08);
	}
	catch(...)
	{
		std::cout << "exception ..." << std::endl;
	}
	return 0;
}

