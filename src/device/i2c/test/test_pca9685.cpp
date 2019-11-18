#include "raspii2c.h"
#include "i2cexception.h"
#include "pca9685.h"
#include "pca9685led.h"
#include "poll.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int main(int argc, char ** argv)
{
	try
	{
		RaspiI2C i2c(argv[1]);

		PCA9685 pwm(0, &i2c);
		pwm.setOutDrv(1);
		pwm.setAutoIncrement(1);
		pwm.setPrescaler(100);
		pwm.setInvertOutput(1);
		pwm.setExternalClock(0, 0);
		//~ pwm.setAllLedsOn();
		//~ pwm.setAllLedsOff();

		int i=0xFF;
		while (i<0xFFF)
		{
			for (u8 port=0; port<16; ++port)
			{
				pwm.getLed(port)->setOffsetON(i);
				pwm.getLed(port)->setOffsetOFF(0xFFF);
				pwm.write(port);
			}
			//~ pwm.writeAll();

			i += 0xF;
			std::cout << i << std::endl;
			poll(0, 0, 100);
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

