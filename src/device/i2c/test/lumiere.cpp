#include "tcs34725.h"
#include "bmp280.h"
#include "raspii2c.h"
#include "i2cexception.h"
#include "log.h"
#include "gpiofactory.h"
#include "gpio.h"
#include <sstream>
#include <thread>
#include <iomanip>

int main(int argc, char **argv)
{
	try
	{
		uint8_t led = 0;

		GpioFactory gpio_factory("/dev/gpiochip0");
		Gpio * gpio = gpio_factory.output(4);
		gpio->write(&led, 1);

		RaspiI2C i2c("/dev/i2c-1");
		TCS34725 capteur_lumiere(&i2c);
		BMP280 capteur_temperature(0, &i2c);
		
		capteur_temperature.reset();

		capteur_temperature.init(0x2, 0x5, 0x3, 0x5, 0x7);
		{
			std::stringstream ss;
			ss << std::endl;
			ss << "BMP280 id : 0x" << std::hex << (int32_t)capteur_temperature.id();
			ss << std::endl;
			ss << "TCS34725 id : 0x" << std::hex << (int32_t)capteur_lumiere.id();
			Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
		}

		while (!capteur_temperature.status());
		{
			double temperature;
			double pression;
			capteur_temperature.measure(&temperature, &pression);
			{
				std::stringstream ss;
				ss << "temperature : " << temperature << " pression : " << pression;
				Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
			}
		}
		
		capteur_lumiere.on(0, 0xFF, 0xFF, 0xFF, 0x0);
		capteur_lumiere.setClearInterruptThreshold(1, 1000, 0xFFFF-1000);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		int32_t cpt=0;
		while(cpt<1000)
		{
			uint8_t AINT;
			uint8_t status = capteur_lumiere.status(&AINT);
			{
				std::stringstream ss;
				ss << "AINT : 0x" << std::hex << (int32_t)AINT << ", STATUS : " << (int32_t)status;
				Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
			}
			if (status)
			{
				uint16_t c, r, g, b;
				capteur_lumiere.read(&c, &r, &g, &b);
				
				std::stringstream ss_color;
				ss_color << "Clear : " << c << ", Red : " << r << ", Green : " << g << ", Blue : " << b;
				Log::getLogger()->debug(__FILE__, __LINE__, ss_color.str());

				++cpt;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}

		capteur_lumiere.off();
		
		gpio = gpio_factory.output(4);
		led = 0;
		gpio->write(&led, 1);
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
