#include "usb_i2c.h"
#include "rs232.h"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << argv[0] << " </dev/ttyUSB0" << std::endl;
		return -1;
	}

	try
	{
		RS232 uart(argv[1]);
		UsbI2C i2c(&uart);

		u8 version = i2c.getVersion();
		std::cout << "version usbI2C : " << (int)version << std::endl;
	}
	catch(...)
	{
		std::cerr << "exception ..." << std::endl;
	}

	return 0;
}
