#ifdef USB_I2C
#include "rs232.h"
#include "rs232factory.h"
#include "usb_i2c.h"
#else
#include "raspii2c.h"
#include <poll.h>
#endif
#include "i2cexception.h"
#include "nunchuk.h"
#include <iostream>
#include <sstream>
#include <iomanip>

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

		Nunchuk wii(0x52, &i2c);
		wii.init();

		while (1)
		{
			try
			{
				wii.lecture();
				std::cout << (int)wii.get_joy_x_axis() << " ";
				std::cout << (int)wii.get_joy_y_axis() << " ";
				std::cout << (int)wii.get_accel_x_axis() << " ";
				std::cout << (int)wii.get_accel_y_axis() << " ";
				std::cout << (int)wii.get_accel_z_axis() << " ";
				std::cout << (int)wii.get_z_button() << " ";
				std::cout << (int)wii.get_c_button() << std::endl;
			}
			catch(I2CException & e)
			{
				std::cout << "exception  " << e.what() << std::endl;
			}

			#ifdef USB_I2C
			factory.scrute(1000);
			#else
			poll(0, 0, 100);
			#endif
			
			wii.init();
		}
		
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

