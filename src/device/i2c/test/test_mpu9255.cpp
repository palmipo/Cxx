#include "i2c.h"
#include "i2cexception.h"
#include "util.h"
#include "mpu9255.h"
#include "mpu9255magneto.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int main(int argc, char ** argv)
{
	try
	{
		I2C i2c(argv[1]);

		MPU9255 gyro(&i2c);
		std::cout << std::hex << "WhoAmI : 0x" << (int)gyro.whoami() << std::endl;

		std::cout << "Temperature : " << std::dec << gyro.temperature() << std::endl;

		gyro.magnetometre()->setConfig(MPU9255_MAGNETO_SINGLE_MEASURE_MODE, MPU9255_MAGNETO_16_BIT_OUTPUT);

		s16 x=0, y=0, z=0;
		gyro.magnetometre()->measure(&x, &y, &z);
		std::cout << "Magnetometre : x = " << x << " y = " << y << " z = " << z << std::endl;
	}
	catch(...)
	{
		std::cerr << "erreur ..." << std::endl;
	}

	return 0;
}
