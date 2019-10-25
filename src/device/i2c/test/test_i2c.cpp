#include "i2c.h"
#include "i2cexception.h"
#include "saa1064.h"
#include "ds1621.h"
#include "ds1307.h"
#include "pcf8583.h"
#include "pia.h"
#include "pcf8574a.h"
#include "pca9685.h"
#include "pca9685led.h"
#include "sg90.h"
#include "nunchuk.h"
#include "raspii2c.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int main(int argc, char ** argv)
{
	try
	{
		RaspiI2C i2c(argv[1]);

		PCF8574A pia1(0, &i2c);
		u8 v = pia1.get();
		std::cout << (int)v << std::endl;

		PCF8574A pia2(1, &i2c);
		
		PCA9685 pwm(0, &i2c);
		SG90 servo(&pwm);

		Nunchuk wii(&i2c);

		s16 angle = 0;
		while (1)
		{
			v = pia2.get();
			std::cout << (int)v << std::endl;

			servo.rotation(0, angle - 90);
			servo.rotation(1, angle - 90);
			angle += 10;
			if (angle > 180) angle = 0;
			
			std::cout << angle << std::endl;

			wii.lecture();
			std::cout << (int)wii.get_joy_x_axis() << " ";
			std::cout << (int)wii.get_joy_y_axis() << " ";
			std::cout << (int)wii.get_accel_x_axis() << " ";
			std::cout << (int)wii.get_accel_y_axis() << " ";
			std::cout << (int)wii.get_accel_z_axis() << " ";
			std::cout << (int)wii.get_z_button() << " ";
			std::cout << (int)wii.get_c_button() << std::endl;

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

