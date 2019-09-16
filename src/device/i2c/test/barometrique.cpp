#include "bmp280.h"
#include "raspii2c.h"
#include "i2cexception.h"
#include "log.h"
#include <sstream>
#include <thread>
#include <iomanip>

int main(int argc, char **argv)
{
	try
	{
		RaspiI2C i2c("/dev/i2c-1");
		BMP280 capteur_barometrique(0, &i2c);
		
		//~ capteur_barometrique.reset();
		//~ std::this_thread::sleep_for(std::chrono::milliseconds(500));

		{
			std::stringstream ss;
			ss << "BMP280 id : 0x" << std::hex << (int32_t)capteur_barometrique.id();
			Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		}

		// osrs_p : *16 ; osrs_t : *2 ; IIR filter : 16
		uint8_t osrs_t = 5;
		uint8_t osrs_p = 5;
		uint8_t mode = 3;
		uint8_t t_sb = 7;
		uint8_t filter = 7;
		capteur_barometrique.init(osrs_t, osrs_p, mode, t_sb, filter);

		int32_t cpt=0;
		while (cpt < 10)
		{
			if (capteur_barometrique.status())
			{
				double temperature;
				double pression;
				capteur_barometrique.measure(&temperature, &pression);
				{
					std::stringstream ss;
					ss << "temperature : " << temperature << " pression : " << pression;
					Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
				}

				int32_t temperature_int32_t;
				int32_t pression_int32_t;
				capteur_barometrique.measure_int32(&temperature_int32_t, &pression_int32_t);
				{
					std::stringstream ss;
					ss << "temperature : " << temperature_int32_t << " pression : " << pression_int32_t;
					Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
				}

				++cpt;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
		}
	}
	catch(I2CException e)
	{
		Log::getLogger()->error(__FILE__, __LINE__, e.what());
	}
	catch(...)
	{
		Log::getLogger()->error(__FILE__, __LINE__, "exception");
	}

	return 0;
}
