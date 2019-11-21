#include "raspii2c.h"
#include "i2cexception.h"
#include "ds2482.h"
#include "ds18b20.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <poll.h>

int main(int argc, char ** argv)
{
	try
	{
		RaspiI2C i2c(argv[1]);

		DS2482 ctrl(0, &i2c);
		ctrl.reset();
		ctrl.setConfig(0, 0, 0);

		ctrl.searchROM();

		DS18B20 thermometre(&ctrl);
		for (int i=0; i<ctrl.nbROM(); ++i)
		{
			std::cout << "rom trouvées : " << std::endl;
			ctrl.rom(i).dump();
			if (ctrl.rom(i).rom(0) == 0x28)
			{
				thermometre.setConfig(i, DS18B20_RESOLUTION_12_BITS, 18, 20);
				thermometre.sauvegarderConfig(i);
			}
		}
		
		while(1)
		{
			for (int i=0; i<ctrl.nbROM(); ++i)
			{
				if (ctrl.rom(i).rom(0) == 0x28)
				{
					//thermometre.scruter(0);
					float temperature = thermometre.temperature(i);
					std::cout << "température : " << temperature << " C" << std::endl;
				}
			}
			
			poll(0, 0, 1000);
		}
		
	}
	catch(I2CException & e)
	{
		std::cout << "exception  i2c " << e.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "exception ..." << std::endl;
	}
	return 0;
}

