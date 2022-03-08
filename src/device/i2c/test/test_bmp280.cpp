#include "i2cexception.h"
#include "bme280.h"
#include "raspii2c.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <thread>
#include <cstdint>

int main(int argc, char ** argv)
{
	try
	{
		RaspiI2C i2c(argv[1]);

		BME280 capteur(0, &i2c);
		std::cout << "id : " << (int)capteur.id() << std::endl;

		capteur.reset();

		capteur.read_coefficients();
		capteur.set_sampling(0b010, 0b101, 0b100, 0b100, 0b101);

		uint32_t raw_temperature = 0;
		uint32_t raw_pression = 0;
		uint32_t raw_humidity = 0;

		capteur.start();
		for (uint32_t i=0; i<10; ++i)
		{
			while (0 != capteur.status())
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			capteur.raw_measure(&raw_temperature, &raw_pression, &raw_humidity);

			capteur.compensate(raw_temperature, raw_pression, raw_humidity);
			std::cout << "temperature : " << raw_temperature << " : " << capteur.temperature << std::endl;
		}
		capteur.stop();
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

