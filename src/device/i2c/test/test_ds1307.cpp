#include "rs232factory.h"
#include "rs232.h"
#include "usb_i2c.h"
//#include "raspii2c.h"
#include "i2cexception.h"
#include "ds1307.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int main(int argc, char ** argv)
{
	try
	{
		// RaspiI2C i2c(argv[1]);

		RS232Factory factory;
		RS232 * uart = factory.add(argv[1]);
		UsbI2C i2c(uart);

		DS1307 rtc(&i2c);
		
		std::stringstream ss;
		ss << "18/01/73";
		rtc.setDate(ss.str().c_str());
		
		char buf[100];
		rtc.date(buf);
		std::cout << buf << std::endl;
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

