#ifdef USBI2C
#include "rs232factory.h"
#include "rs232.h"
#include "usb_i2c.h"
#else
#include "raspii2c.h"
#endif
#include "i2cexception.h"
#include "pca9685.h"
#include "pca9685led.h"
#include "sg90.h"
#include <poll.h>
#include <iostream>
#include <sstream>
#include <iomanip>

int main(int argc, char ** argv)
{
	try
	{
		#ifdef USBI2C
		RS232Factory factory;
		RS232 * serial = factory.addSerialConnection(argv[1]);
		serial->setConfig(B19200, 8, 'N', 1);
		UsbI2C i2c(serial);
		#else
		RaspiI2C i2c(argv[1]);
		#endif
		PCA9685 pwm(0, &i2c);
		SG90 servo(&pwm);

		s16 angle = 0;
		while (1)
		{
			servo.rotation(0, angle - 90);
			servo.rotation(1, angle - 90);
			angle += 10;
			if (angle > 180)  angle = 0;
			
			std::cout << angle << std::endl;

			poll(0, 0, 1000);
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

