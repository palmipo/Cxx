#include "raspii2c.h"
#include "i2cexception.h"
#include "mcp23017.h"
#include "tempo.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int main(int argc, char ** argv)
{
	try
	{
		RaspiI2C i2c("/dev/i2c-1");

		MCP23017 pia(0, &i2c);
		
		pia.init(0);
		pia.init(1);
		pia.set(0, 0);
		pia.set(1, 0);

		Tempo::minutes(10);
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

