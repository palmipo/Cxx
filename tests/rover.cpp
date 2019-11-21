#include "i2c.h"
#include "i2cexception.h"
#include "ds1307.h"
#include "mcp23017.h"
#include "pca9685.h"
#include "pca9685led.h"
#include "sg90.h"
#include "batrasocket.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <iomanip>

static void reception(BatraSocketItem * sock, void * data)
{
}

int main(int argc, char ** argv)
{
	try
	{
		I2C i2c(argv[1]);

		DS1307 clk(0, &i2c);

		MCP23017 pia(0, &i2c);
		pia.init(0, 1, 0, 0, 1, 0, 0);	// input
		pia.init(1, 0);			// output

		PCA9685 pwm(0, &i2c);

		SG90 servo(&pwm);

		BatraSocket sock;
		sock.listen("127.0.0.1", 2222);
		sock.registerRecvCallback(reception, &pia);

		pia.set(1, 0x05);

		//~ pwm.setOutDrv(1);
		//~ pwm.setAutoIncrement(1);
		//~ pwm.setPrescaler(3);
		//~ pwm.setInvertOutput(0);
		//~ pwm.setExternalClock(0, 0);

		servo.rotation(2, 90.);
		servo.rotation(3, 90.);
		servo.rotation(4, 90.);
		servo.rotation(5, 90.);
		servo.rotation(6, 90.);
		servo.rotation(7, 90.);

		pwm.getLed(0)->setOffsetON(0);
		pwm.getLed(0)->setOffsetOFF(0xFFF);
		pwm.getLed(1)->setOffsetON(0);
		pwm.getLed(1)->setOffsetOFF(0xFFF);
		pwm.writeAll();

		while (1)
		{
			if (0 == sock.scrute(1000))
			{
				pia.set(1, 0);
			}
		}
		
		pwm.setOutDrv(0);
		pia.set(1, 0);
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

