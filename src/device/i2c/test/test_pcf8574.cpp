#include "i2c.h"
#include "i2cexception.h"
#include "pcf8574at.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int main(int argc, char ** argv)
{
	try
	{
		I2C i2c("/dev/i2c-1");

		PCF8574AT pia(&i2c);
		pia.setDirection(0);
		pia.set(0x08);
	}
	catch(...)
	{
		std::cout << "exception ..." << std::endl;
	}
	return 0;
}

