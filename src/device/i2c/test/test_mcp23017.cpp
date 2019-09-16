#ifdef USB_I2C
#include "rs232.h"
#include "rs232factory.h"
#include "usb_i2c.h"
#else
#include "raspii2c.h"
#endif
#include "i2cexception.h"
#include "mcp23017.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <poll.h>

int main(int argc, char ** argv)
{
	try
	{
#ifdef USB_I2C
		RS232Factory factory;
		RS232 * serial = factory.addSerialConnection(argv[1]);
		UsbI2C i2c(serial);
#else
		RaspiI2C i2c(argv[1]);
#endif

		MCP23017 pia(0, &i2c);
		
		pia.init(0);
		pia.init(1);
		pia.set(0, 0);
		pia.set(1, 0);

		// while (1)
		// {
		// }

		poll(0, 0, 60000);

#ifdef USB_I2C
		factory.closeAll();
#endif
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

